/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/18 13:31:40 by jmaia            ###   ###               */
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
#include "poll.hpp"

int	main(int ac, char **av)
{
	int				err;
	unsigned short	port;
	std::string		password;

	err = parseArgs(ac, av, port, password);
	if (err)
		return (err);
	int listenFd = initSocketOrPrintError(port);
	if (listenFd < 0)
		return (2);
	signal(SIGINT, sigintHandler);
	pollRoutine(listenFd, password);
}
