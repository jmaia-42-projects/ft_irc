/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/09 10:19:43 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "parser.hpp"

int	main(int ac, char **av)
{
	/*int	err;

	err = check_args_validity(ac, av);
	if (err)
		return (err);*/
	(void)ac;
	(void)av;

	const int PORT = 3333;

	int socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1)
	{
		std::cout << "Error: socket creation failed" << std::endl;
		return (1);
	}
	std::cout << "Socket created" << std::endl;

	struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;  
    serverAddress.sin_addr.s_addr = INADDR_ANY;  
    serverAddress.sin_port = htons(PORT);
	if (bind(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		std::cout << "Error: bind failed" << std::endl;
		return (1);
	}
	std::cout << "Bind done on port " << PORT << std::endl;

	const int maxPendingConnections = 10;
	if (listen(socketFd, maxPendingConnections) < 0)
	{
		std::cout << "Error: listen failed" << std::endl;
		return (1);
	}
	std::cout << "Listening started... " << std::endl;

	struct sockaddr_in clientAddress;
	socklen_t clientAddressLength = sizeof(clientAddress);
	int clientSocketFd = accept(socketFd, (struct sockaddr *)&clientAddress, &clientAddressLength);
	if (clientSocketFd < 0)
	{
		std::cout << "Error: accept failed" << std::endl;
		return (1);
	}
	std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << " using port " << ntohs(clientAddress.sin_port) << std::endl;

	close(clientSocketFd);
    close(socketFd);
}
