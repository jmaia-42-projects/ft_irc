/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:54:34 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/16 18:16:07 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "initSocket.hpp"

static struct sockaddr_in6	getAddr(unsigned short port);

int	initSocketOrPrintError(unsigned short port)
{
	int	fd;

	fd = initSocket(port);
	switch (fd)
	{
		case -1:
			perror("Socket error");
			return (-1);
		case -2:
			perror("Bind error");
			return (-2);
		case -3:
			perror("Listen error");
			return (-3);
	}
	return (fd);
}

int	initSocket(unsigned short port)
{
	int					err;
	int					fd;
	struct sockaddr_in6	addr;
	int					unused = 1;

	fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (fd == -1)
		return (-1);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &unused, sizeof(int));
	addr = getAddr(port);
	err = bind(fd, (const sockaddr *)&addr, sizeof(addr));
	if (err == -1)
	{
		close(fd);
		return (-2);
	}
	err = listen(fd, 128);
	if (err == -1)
	{
		close(fd);
		return (-3);
	}
	return (fd);
}

static struct sockaddr_in6	getAddr(unsigned short port)
{
	struct sockaddr_in6	addr6;

	addr6.sin6_family = AF_INET6;
	addr6.sin6_port = htons(port);
	addr6.sin6_flowinfo = 0;
	addr6.sin6_addr = in6addr_any;
	addr6.sin6_scope_id = 0;
	return (addr6);
}
