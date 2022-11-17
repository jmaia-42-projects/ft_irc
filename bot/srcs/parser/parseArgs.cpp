/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseArgs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:08:04 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/17 13:26:19 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "convert.hpp"

int	parseArgs(int ac, char **av, std::string &address, unsigned short &port, std::string &password)
{
	int	err;

	err = checkArgsValidityAndPrintError(ac, av);
	if (err)
		return (err);
	address = av[1];
	port = (unsigned short) toInt(std::string(av[2]));
	password = std::string(av[3]);
	return (0);
}
