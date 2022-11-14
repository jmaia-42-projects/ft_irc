/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:18:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 14:29:03 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Client.hpp"
#include "messages.hpp"

int     Client::_globalId = 0;

Client::Client(void): _id(_globalId++), _socket(-1), _givedPassword(false), _nickname(""), _logged(false), _username(""), _realname("")
{
}

Client::Client(int socket): _socket(socket), _givedPassword(false),  _nickname(""), _logged(false), _username(""), _realname("")
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
        _logged = rhs._logged;
        _username = rhs._username;
        _realname = rhs._realname;
        _givedPassword = rhs._givedPassword;
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

void Client::setUsername(std::string username)
{
    _username = username;
}
std::string Client::getUsername(void) const
{
    return _username;
}
void Client::setRealname(std::string realname)
{
    _realname = realname;
}
std::string Client::getRealname(void) const
{
    return _realname;
}
void Client::log(void)
{
    _logged = true;
}
bool Client::isLogged(void) const
{
    return _logged;
}
void Client::givePassword(void)
{
    _givedPassword = true;
}
bool Client::hasGivedPassword(void) const
{
    return _givedPassword;
}

void Client::receiveMessage(std::string message)
{
	sendMessage(*this, message);
}
