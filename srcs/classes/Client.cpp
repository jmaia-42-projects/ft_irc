/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:18:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/10 18:09:10 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

Client::Client(void): _socket(-1)
{
}

Client::Client(int socket): _socket(socket)
{
    _pollfd.fd = socket;
    _pollfd.events = POLLIN | POLLOUT;
}

Client::Client(Client const & src)
{
    *this = src;
}

Client::~Client(void)
{
}

Client & Client::operator=(Client const & rhs)
{
    if (this != &rhs)
    {
        this->_socket = rhs._socket;
        this->_pollfd = rhs._pollfd;
    }
    return *this;
}

struct pollfd Client::getPollFd(void) const
{
    return _pollfd;
}

int Client::getSocket(void) const
{
    return _socket;
}