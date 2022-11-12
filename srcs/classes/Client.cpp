/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:18:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 16:25:31 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

int     Client::_globalId = 0;

Client::Client(void): _id(_globalId++), _socket(-1), _nickname("")
{
}

Client::Client(int socket): _socket(socket),  _nickname("")
{
    _id = _globalId++;
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
        _id = rhs._id;
        _socket = rhs._socket;
        _pollfd = rhs._pollfd;
        _nickname = rhs._nickname;
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

int Client::getId(void) const
{
    return _id;
}

void Client::setNickname(std::string nickname)
{
    _nickname = nickname;
}
std::string Client::getNickname(void) const
{
    return _nickname;
}