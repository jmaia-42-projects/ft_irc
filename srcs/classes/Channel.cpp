/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:18:17 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 16:26:54 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "messages.hpp"
#include "colors.hpp"

Channel::Channel(): _name(""), _topic("") {}

Channel::Channel(std::string name, Client &client): _name(name), _topic("")
{
	std::cout << PURPLE << "Created channel " << _name << RESET << std::endl;
	_modes.insert(std::make_pair('l', 0));
	_modes.insert(std::make_pair('i', 0));
	_modes.insert(std::make_pair('t', 1));
	this->addOperator(&client);
	this->addMember(&client);
}
Channel::Channel(const Channel & src) { *this = src; }
Channel::~Channel() {}
Channel & Channel::operator=(const Channel & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_topic = rhs._topic;
		this->_clients = rhs._clients;
		this->_operators = rhs._operators;
		this->_modes = rhs._modes;
	}
	return *this;
}

bool        Channel::isMember(Client & client) const
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->getId() == client.getId())
			return true;
	}
	return false;
}

void	Channel::sendMessageToAll(std::string msg) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		sendMessage(*_clients[i], msg);
}

void        Channel::addMember(Client *client)
{
	if (!this->isMember(*client))
	{
		if (_modes['l'] > 0 && _clients.size() >= _modes['l'])
		{
			sendMessage(*client, "471 " + client->getNickname() + " " + _name + " :Cannot join channel (+l)");
			return ;
		}
		for(size_t i = 0; i < _clients.size(); i++)
		{
			std::cout << "Client " << _clients[i]->getNickname() << " (with id: " << _clients[i]->getId() << ") in channel " << _name << std::endl;
		}
		_clients.push_back(client);
		std::cout << "Added client " << client->getNickname() << " to channel " << _name << RESET << std::endl;
		for(size_t i = 0; i < _clients.size(); i++)
		{
			std::cout << "Client " << _clients[i]->getNickname() << " (with id: " << _clients[i]->getId() << ") in channel " << _name << std::endl;
		}
		sendMessageToAll(":" + client->getIdentifier() + " JOIN " + _name);
		this->sendTopic(*client);
		this->sendUserList(*client);
	}
}
void        Channel::removeMember(Client & client, std::string reason)
{
	std::cout << "Removing member " << client.getNickname() << " from channel " << _name << std::endl;
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if ((*it)->getId() == client.getId())
		{
			sendMessageToAll(":" + (*it)->getIdentifier() + " PART " + _name + (reason == "" ? "" : " :") + reason);
			this->_clients.erase(it);
			if (this->isOperator(client))
				this->removeOperator(client);
			return;
		}
	}
}
void        Channel::removeMember(Client & client) { this->removeMember(client, ""); }

bool        Channel::isOperator(Client & client) const { return this->isOperator((const Client &)client); }
bool        Channel::isOperator(const Client & client) const
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i]->getId() == client.getId())
			return true;
	}
	return false;
}
void        Channel::addOperator(Client *client)
{
	std::cout << "add operator " << client->getNickname() << std::endl;
	if (!this->isOperator(*client))
		this->_operators.push_back(client);
}
void        Channel::removeOperator(Client & client)
{
	for (std::vector<Client *>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
	{
		if ((*it)->getId() == client.getId())
		{
			this->_operators.erase(it);
			return;
		}
	}
}

std::string Channel::getName() const { return this->_name; }
bool Channel::isChannelNameValid(std::string name)
{
	if (name.length() < 2 || name.length() > 200)
		return false;
	if (name[0] != '#')
		return false;
	for (std::string::iterator it = name.begin() + 1; it != name.end(); it++)
	{
		if (*it == ' ' || *it == ',')
			return false;
	}
	return true;
}

std::string Channel::getTopic() const { return this->_topic; }
void        Channel::setTopic(std::string topic, Client &modifier) {
	if (_modes['t'] == 1 && !isOperator(modifier))
	{
		sendMessage(modifier, "482 " + _name + " :You're not channel operator");
		return ;
	}
	this->_topic = topic;
	sendMessageToAll(":" + modifier.getIdentifier() + " TOPIC " + _name + " :" + topic);
}
void    Channel::sendTopic(Client &client) const
{
	if (_topic != "")
		sendMessage(client, "332 " + client.getIdentifier() + " " + _name + " :" + _topic);
}

void    Channel::sendUserList(Client &client) const
{
	std::string userList = "";
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (i != 0)
			userList += " ";
		if (this->isOperator(*(_clients.at(i))))
			userList += "@";
		userList += _clients.at(i)->getNickname();
	}
	sendMessage(client, "353 " + client.getIdentifier() + " = " + _name + " :" + userList);
	sendMessage(client, "366 " + client.getIdentifier() + " " + _name + " :End of /NAMES list");
}

void Channel::receiveMessage(std::string message)
{
	sendMessageToAll(message);
}

void	Channel::changeMode(ModeModificatior &modeModificator, Client &modifier)
{
	if (!modeModificator.activate())
		_modes[modeModificator.getMode()] = 0;
	else
	{
		if (modeModificator.getMode() != 'o')
		{
			if (modeModificator.getParameter() != "")
				_modes[modeModificator.getMode()] = atoi(modeModificator.getParameter().c_str());
			else
				_modes[modeModificator.getMode()] = 1;
		}
		else
		{
			for (size_t i = 0; i < _clients.size(); i++)
			{
				if (_clients[i]->getNickname() == modeModificator.getParameter())
				{
					if (modeModificator.activate())
						this->addOperator(_clients[i]);
					else
						this->removeOperator(*_clients[i]);
				}
			}
		}
	}
	sendMessageToAll(":" + modifier.getIdentifier() + " MODE " + _name + " " + (modeModificator.activate() ? "+" : "-") + modeModificator.getMode() + (modeModificator.getParameter() == "" ? "" : " " + modeModificator.getParameter()));
}

std::string	Channel::getName(void)
{
	return (this->_name);
}
