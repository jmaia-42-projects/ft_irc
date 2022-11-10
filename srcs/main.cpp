/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/10 13:40:47 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <errno.h>
#include <string.h>
#include <poll.h>

#include "parser.hpp"

#define PORT 3333
#define POLL_SIZE 1024

int	main(int ac, char **av)
{
	/*int	err;

	err = check_args_validity(ac, av);
	if (err)
		return (err);*/
	(void)ac;
	(void)av;

	struct pollfd pollSet[POLL_SIZE];
	int	inPoll = 0;

	int serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocketFd == -1)
	{
		std::cout << "Error: socket creation failed: " << strerror(errno) << std::endl;
		return (1);
	}
	std::cout << "Socket created" << std::endl;

	struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;  
    serverAddress.sin_addr.s_addr = INADDR_ANY;  
    serverAddress.sin_port = htons(PORT);
	if (bind(serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		std::cout << "Error: bind failed: " << strerror(errno) << std::endl;
		return (1);
	}
	std::cout << "Bind done on port " << PORT << std::endl;

	pollSet[0].fd = serverSocketFd;
    pollSet[0].events = POLLIN;
    inPoll++;

	listen(serverSocketFd, 5);

	while (1)
	{
		poll(pollSet, inPoll, 1000);
		for(int i = 0; i < inPoll; i++)
		{
			if(pollSet[i].revents & POLLIN)
			{
				if(pollSet[i].fd == serverSocketFd)
				{
					//Read on server socket => new connection
					std::cout << "New connection" << std::endl;
					struct sockaddr_in clientAddress;
			       	socklen_t clientAddressLength = sizeof(clientAddress);
			      	int clientserverSocketFd = accept(serverSocketFd, (struct sockaddr *)&clientAddress, &clientAddressLength);
					if (clientserverSocketFd == -1)
					{
						std::cout << "Error: accept failed: " << strerror(errno) << std::endl;
						return (1);
					}
					pollSet[inPoll].fd = clientserverSocketFd;
					pollSet[inPoll].events = POLLIN;
					inPoll++;
				}
				else
				{
					//Read on client socket => new message
					std::cout << "New message" << std::endl;
					char buffer[1024];
					bzero(buffer, 1024);
					int n = read(pollSet[i].fd, buffer, 1024);
					if (n == -1)
					{
						std::cout << "Error: read failed: " << strerror(errno) << std::endl;
						return (1);
					}
					else
					{
						std::cout << buffer << std::endl;
						if(strcmp(buffer, "exit") == 0)
						{
							for(int j = 0; j < inPoll; j++)
							{
								close(pollSet[j].fd);
							}
							close(serverSocketFd);
							return (0);
						}
					}
				}
			}
		}
	}
}
