/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_validity.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:05:10 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/08 22:14:07 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "convert.hpp"

static bool	is_password_valid(char *raw_password);
static bool	is_port_valid(char *raw_port);

int	check_args_validity(int ac, char **av)
{
	if (ac != 3)
		return (1);
	if (!is_port_valid(av[1]))
		return (2);
	if (!is_password_valid(av[2]))
		return (3);
	return (0);
}

static bool	is_port_valid(char *raw_port)
{
	std::string	str_port;
	int			port;

	if (!raw_port)
		return (false);
	str_port = std::string(raw_port);
	if (str_port.empty() || !is_number(str_port))
		return (false);
	port = to_int(str_port);
	if (port < 0 || port > 65535)
		return (false);
	return (true);
}

static bool	is_password_valid(char *raw_password)
{
	(void) raw_password;
	return (true);
}
