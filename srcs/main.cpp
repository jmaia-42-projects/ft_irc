/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/11 18:35:00 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>

#include "initSocket.hpp"
#include "parser.hpp"

int	main(int ac, char **av)
{
	int				err;
	int				listenFd;
	unsigned short	port;
	std::string		password;

	err = parseArgs(ac, av, port, password);
	if (err)
		return (1);
	listenFd = initSocketOrPrintError(port);
	if (!listenFd)
		return (2);
}
