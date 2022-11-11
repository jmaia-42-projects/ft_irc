/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseArgs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:08:04 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/11 18:41:16 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "convert.hpp"

int	parseArgs(int ac, char **av, unsigned short &port, std::string &password)
{
	int	err;

	err = checkArgsValidityAndPrintError(ac, av);
	if (err)
		return (err);
	port = (unsigned short) toInt(std::string(av[1]));
	password = std::string(av[2]);
	return (0);
}
