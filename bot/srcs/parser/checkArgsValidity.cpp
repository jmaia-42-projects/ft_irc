/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgsValidity.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:05:10 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/17 13:30:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ostream>

#include "parser.hpp"
#include "convert.hpp"

static bool	isPortValid(char *rawPort);

int	checkArgsValidityAndPrintError(int ac, char **av)
{
	int	err;

	err = checkArgsValidity(ac, av);
	switch (err)
	{
		case 1:
			std::cerr << "Usage: " << av[0] << " <address> <port> <password>" << std::endl;
			break;
		case 2:
			std::cerr << "Port is invalid !" << std::endl;
			break;
		case 3:
			std::cerr << "Password is invalid !" << std::endl;
			break;
	}
	return (err);
}

int	checkArgsValidity(int ac, char **av)
{
	if (ac != 4)
		return (1);
	if (!isPortValid(av[2]))
		return (2);
	return (0);
}

static bool	isPortValid(char *rawPort)
{
	std::string	strPort;
	int			port;

	if (!rawPort)
		return (false);
	strPort = std::string(rawPort);
	if (strPort.empty() || !isNumber(strPort))
		return (false);
	port = toInt(strPort);
	if (port < 0 || port > 65535)
		return (false);
	return (true);
}
