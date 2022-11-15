/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:18:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 18:06:34 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Client.hpp"
#include "messages.hpp"

int     Client::_globalId = 0;

Client::Client(void): _id(_globalId++), _socket(-1), _givedPassword(false), _nickname(""), _logged(false), _username(""), _realname(""), _recvBuffer(""), _disconnected(false)
{
}

Client::Client(int socket): _socket(socket), _givedPassword(false),  _nickname(""), _logged(false), _username(""), _realname(""), _recvBuffer(""), _disconnected(false)
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
		_id = rhs.getId();
		_socket = rhs.getSocket();
		_pollfd = rhs.getPollFd();
		_nickname = rhs.getNickname();
		_logged = rhs.isLogged();
		_username = rhs.getUsername();
		_realname = rhs.getRealname();
		_givedPassword = rhs.hasGivedPassword();
		_recvBuffer = rhs.getRecvBuffer();
		_disconnected = rhs.isDisconnected();
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

void Client::receiveMessage(std::string message, Client &client)
{
	(void) client;
	sendMessage(*this, message);
}

std::string	Client::getIdentifier(void) const
{
	return _nickname + "!" + _username + "@localhost";
}

std::string Client::getRecvBuffer(void) const
{
	return _recvBuffer;
}

void Client::setRecvBuffer(std::string buffer)
{
	_recvBuffer = buffer;
}

bool	Client::isDisconnected(void) const
{
	return _disconnected;
}
void	Client::disconnect(void)
{
	_disconnected = true;
}

std::string	Client::getName(void)
{
	return (this->_nickname);
}

bool	Client::operator==(Client const &obj)
{
	return (obj._nickname == this->_nickname);
}
