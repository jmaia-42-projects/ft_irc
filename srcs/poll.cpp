/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:19:38 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/10 17:40:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <poll.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <iostream>
#include "Client.hpp"

#define POLL_SIZE 1024

struct pollfd *exportPollSet(struct pollfd *pollSet, int serverSocket, std::vector<Client> &clients)
{
    pollSet[0].fd = serverSocket;
    pollSet[0].events = POLLIN;
    for (size_t i = 0; i < clients.size(); i++)
        pollSet[i + 1] = clients.at(i).getPollFd();
    return pollSet;
}

void    acceptConnection(int serverSocket, std::vector<Client> &clients)
{
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
	int clientserverSocketFd = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
	if (clientserverSocketFd == -1)
	{
		std::cout << "Error: accept failed: " << strerror(errno) << std::endl;
		return;
	}
    std::cout << "New connection" << std::endl;
    clients.push_back(Client(clientserverSocketFd));
}

void    acceptMessage(Client &client)
{
    (void)client;
}

void    pollRoutine(int serverSocket)
{
    std::vector<Client> clients;
    int                 inPoll;
    
    while (1)
    {
        inPoll = clients.size() + 1;
        struct pollfd pollSet[inPoll];
        exportPollSet(pollSet, serverSocket, clients);
        poll(pollSet, inPoll, -1);
        for (int i = 0; i < inPoll; i++)
        {
            if (pollSet[i].revents == POLLIN)
            {
                if (pollSet[i].fd == serverSocket)
                    acceptConnection(serverSocket, clients);
                else
                    acceptMessage(clients.at(i - 1));
            }
        }
    }
}