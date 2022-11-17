/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/17 12:45:33 by dhubleur         ###   ########.fr       */
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
#include "signal.hpp"

#define PORT 3333

void    pollRoutine(int serverSocket);

int	main(int ac, char **av)
{
	int	err;
	err = checkArgsValidity(ac, av);
	if (err)
		return (err);
	int listenFd = initSocketOrPrintError(PORT);
	if (listenFd < 0)
		return (2);
	signal(SIGINT, sigintHandler);
	pollRoutine(listenFd);
}
