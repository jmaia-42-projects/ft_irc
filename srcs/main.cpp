/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/12 16:30:43 by dhubleur         ###   ########.fr       */
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

#include "initSocket.hpp"
#include "parser.hpp"

#define PORT 3333

void    pollRoutine(int serverSocket);

int	main(int ac, char **av)
{
	
	/*int	err;
	err = check_args_validity(ac, av);
	if (err)
		return (err);*/
	(void)ac;
	(void)av;

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

	listen(serverSocketFd, 5);

	pollRoutine(serverSocketFd);
}
