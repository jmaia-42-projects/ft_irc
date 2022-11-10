/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgsValidity.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:05:10 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/10 11:52:25 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "convert.hpp"

static bool	isPasswordValid(char *rawPassword);
static bool	isPortValid(char *rawPort);

int	checkArgsValidity(int ac, char **av)
{
	if (ac != 3)
		return (1);
	if (!isPortValid(av[1]))
		return (2);
	if (!isPasswordValid(av[2]))
		return (3);
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

static bool	isPasswordValid(char *rawPassword)
{
	(void) rawPassword;
	return (true);
}
