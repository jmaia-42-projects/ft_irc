/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:19:38 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 13:40:45 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "poll.hpp"
#include "colors.hpp"

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
	std::cout << GREEN << "New client with id: " << client.getId() << RESET << std::endl;
	clients.push_back(client);
}

std::string acceptMessage(Client &client)
{
	std::string message;
	char        buffer[REVC_BUFFER];
	int         readed;

	bzero(buffer, REVC_BUFFER);
	readed = recv(client.getSocket(), buffer, REVC_BUFFER, MSG_DONTWAIT);
	if (readed == -1)
	{
		std::cout << "Error: recv failed: " << strerror(errno) << std::endl;
		return message;
	}
	message.append(buffer, readed);
	return message;
}

void	reveiveMessage(Client &client, std::vector<Client> &clients, int j, std::vector<Channel> &channels)
{
	std::string message = acceptMessage(client);
	if (message.length() > 0)
		treatMessage(message, client, clients, channels);
	else
	{
		std::cout << RED << "Client " << client.getId() << " disconnected" << RESET << std::endl;
		clients.erase(clients.begin() + j);
	}
}

void	treatPollFd(struct pollfd &pollSet, int serverSocket, std::vector<Client> &clients, std::vector<Channel> &channels)
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
					if (clients.at(j).isDisconnected())
					{
						std::cout << RED << "Client " << clients.at(j).getId() << " disconnected" << RESET << std::endl;
						clients.erase(clients.begin() + j);
					}
					else
						reveiveMessage(clients.at(j), clients, j, channels);
					break;
				}
			}
		}
	}
}

void pollRoutine(int serverSocket)
{
	std::vector<Client> clients;
	std::vector<Channel> channels;
	size_t inPoll;

	while (1)
	{
		inPoll = clients.size() + 1;
		struct pollfd pollSet[inPoll];
		exportPollSet(pollSet, serverSocket, clients);
		poll(pollSet, inPoll, -1);
		for (size_t i = 0; i < inPoll; i++)
			treatPollFd(pollSet[i], serverSocket, clients, channels);
	}
}