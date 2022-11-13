/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:19:38 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/13 13:02:53 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "poll.hpp"

void exportPollSet(struct pollfd *pollSet, int serverSocket, std::vector<Client> &clients)
{
    pollSet[0].fd = serverSocket;
    pollSet[0].events = POLLIN;
    for (size_t i = 0; i < clients.size(); i++)
        pollSet[i + 1] = clients.at(i).getPollFd();
}

void acceptConnection(int serverSocket, std::vector<Client> &clients)
{
    struct sockaddr_in  clientAddress;
    socklen_t           clientAddressLength = sizeof(clientAddress);

    int clientserverSocketFd = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientserverSocketFd == -1)
    {
        std::cout << "Error: accept failed: " << strerror(errno) << std::endl;
        return;
    }
    Client client(clientserverSocketFd);
    std::cout << "New connection: Client " << client.getId() << std::endl;
    clients.push_back(client);
}

std::string acceptMessage(Client &client)
{
    std::string message;
    char        buffer[REVC_BUFFER];
    int         readed;

    bzero(buffer, REVC_BUFFER);
    while ((readed = recv(client.getSocket(), buffer, REVC_BUFFER, MSG_DONTWAIT)) > 0)
    {
        if (readed == -1)
        {
            std::cout << "Error: recv failed: " << strerror(errno) << std::endl;
            break;
        }
        message.append(buffer, readed);
        bzero(buffer, REVC_BUFFER);
    }
    return message;
}

void treatPollFd(struct pollfd &pollSet, int serverSocket, std::vector<Client> &clients)
{
    if (pollSet.revents & POLLIN)
    {
        if (pollSet.fd == serverSocket)
            acceptConnection(serverSocket, clients);
        else
        {
            for (size_t j = 0; j < clients.size(); j++)
            {
                if (clients.at(j).getSocket() == pollSet.fd)
                {
                    Client &client = clients.at(j);
                    std::string message = acceptMessage(client);
                    if (message.length() > 0)
                    {
                        std::cout << "------ New message received from client " << client.getId() << " ------" << std::endl
                                  << message << std::endl;
                        treatMessage(message, client, clients);
                    }
                    else
                    {
                        std::cout << "Client " << client.getId() << " disconnected" << std::endl;
                        clients.erase(clients.begin() + j);
                    }
                }
            }
        }
    }
}

void pollRoutine(int serverSocket)
{
    std::vector<Client> clients;
    size_t inPoll;

    while (1)
    {
        inPoll = clients.size() + 1;
        struct pollfd pollSet[inPoll];
        exportPollSet(pollSet, serverSocket, clients);
        poll(pollSet, inPoll, -1);
        for (size_t i = 0; i < inPoll; i++)
            treatPollFd(pollSet[i], serverSocket, clients);
    }
}