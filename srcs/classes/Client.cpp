/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:18:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 18:13:39 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>

#include "Client.hpp"
#include "messages.hpp"
#include "colors.hpp"

int     Client::_globalId = 0;

Client::Client(void): _id(_globalId++), _socket(-1), _givedPassword(false), _nickname(""), _logged(false), _username(""), _realname(""), _recvBuffer(""), _operator(false)
{
}

Client::Client(int socket): _socket(socket), _givedPassword(false),  _nickname(""), _logged(false), _username(""), _realname(""), _recvBuffer(""), _operator(false)
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
		_operator = rhs.isOperator();
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


void	Client::disconnect(std::vector<Client> &clients)
{
	std::cout << RED << "Client " << _id << " disconnected" << RESET << std::endl;
	if(close(_socket) < 0)
		std::cout << "Error during socket closing" << std::endl;
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->getId() == _id)
		{
			clients.erase(it);
			break;
		}
	}
}

std::string	Client::getName(void)
{
	return (this->_nickname);
}

bool	Client::operator==(Client const &obj)
{
	return (obj._nickname == this->_nickname);
}

bool	Client::isOperator(void) const
{
	return (_operator);
}
void	Client::setOperator(void)
{
	_operator = true;
}