/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:18:17 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 15:49:49 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "messages.hpp"
#include "colors.hpp"
#include "numericReplies.hpp"

Channel::Channel(std::string name, Client &client, std::vector<Client> &clients): _global_clients(clients), _name(name), _topic("")
{
	std::cout << PURPLE << "Created channel " << _name << RESET << std::endl;
	_modes.insert(std::make_pair('l', 0));
	_modes.insert(std::make_pair('i', 0));
	_modes.insert(std::make_pair('t', 1));
	_modes.insert(std::make_pair('m', 0));
	this->addOperator(&client);
	this->addMember(&client);
}
Channel::Channel(const Channel & src): _global_clients(src._global_clients) { *this = src; }
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
		if (_clients[i] == client.getNickname())
			return true;
	}
	return false;
}

void	Channel::sendMessageToAll(std::string msg) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		sendMessage(*getClientByNickname(_clients.at(i)), msg);
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
		if (_modes['i'] > 0 && !isOperator(*client))
		{
			bool found = false;
			for (size_t i = 0; i < _invited.size(); i++)
			{
				if (_invited.at(i) == client->getNickname())
					found = true;
			}
			if (!found)
			{
				sendMessage(*client, "473 " + client->getNickname() + " " + _name + " :Cannot join channel (+i)");
				return ;
			}
		}
		if (isBanned(*client))
		{
			sendMessage(*client, "474 " + client->getNickname() + " " + _name + " :Cannot join channel (+b)");
			return ;
		}
		_clients.push_back(client->getNickname());
		sendMessageToAll(":" + client->getIdentifier() + " JOIN " + _name);
		this->sendTopic(*client);
		this->sendUserList(*client);
	}
}
void        Channel::removeMember(Client & client, std::string reason)
{
	for (std::vector<std::string>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (*it == client.getNickname())
		{
			sendMessageToAll(":" + getClientByNickname(*it)->getIdentifier() + " PART " + _name + (reason == "" ? "" : " :") + reason);
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
		if (_operators[i] == client.getNickname())
			return true;
	}
	return false;
}
void        Channel::addOperator(Client *client)
{
	if (!this->isOperator(*client))
		this->_operators.push_back(client->getNickname());
}
void        Channel::removeOperator(Client & client)
{
	for (std::vector<std::string>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
	{
		if (*it == client.getNickname())
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
		if (this->isOperator(*getClientByNickname(_clients.at(i))))
			userList += "@";
		userList += _clients.at(i);
	}
	sendMessage(client, "353 " + client.getIdentifier() + " = " + _name + " :" + userList);
	sendMessage(client, "366 " + client.getIdentifier() + " " + _name + " :End of /NAMES list");
}

void Channel::receiveMessage(std::string message, Client &client)
{
	if (isBanned(client))
		return ;
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i] != client.getNickname())
			sendMessage(*getClientByNickname(_clients[i]), message);
	}
}

void	Channel::changeMode(ModeModificatior &modeModificator, Client &modifier)
{
	if (modeModificator.getMode() == 'b')
	{
		if (modeModificator.activate())
			_banned.push_back(modeModificator.getParameter());
		else
		{
			for (size_t i = 0; i < _banned.size(); i++)
			{
				if (_banned[i] == modeModificator.getParameter())
				{
					_banned.erase(_banned.begin() + i);
					break ;
				}
			}
		}
	}
	else if (modeModificator.getMode() == 'o')
	{
		for (size_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i] == modeModificator.getParameter())
			{
				if (modeModificator.activate())
					this->addOperator(getClientByNickname(_clients.at(i)));
				else
					this->removeOperator(*getClientByNickname(_clients.at(i)));
			}
		}
	}
	else if (!modeModificator.activate())
		_modes[modeModificator.getMode()] = 0;
	else
	{
		if (modeModificator.getMode() == 'l')
		{
			if (atoi(modeModificator.getParameter().c_str()) > 0)
				_modes[modeModificator.getMode()] = atoi(modeModificator.getParameter().c_str());
			else
				return ;
		}
		else
			_modes[modeModificator.getMode()] = 1;
	}
	sendMessageToAll(":" + modifier.getIdentifier() + " MODE " + _name + " " + (modeModificator.activate() ? "+" : "-") + modeModificator.getMode() + (modeModificator.getParameter() == "" ? "" : " " + modeModificator.getParameter()));
}

bool	Channel::isBanned(Client &client)
{
	for (size_t i = 0; i < _banned.size(); i++)
	{
		if (_banned[i] == client.getNickname())
			return true;
	}
	return false;
}

std::string	Channel::getName(void)
{
	return (this->_name);
}


Client*	Channel::getClientByNickname(std::string nickName) const
{
	for (size_t i = 0; i < _global_clients.size(); i++)
	{
		if (_global_clients[i].getNickname() == nickName)
			return (&(_global_clients[i]));
	}
	return (NULL);
}

void		Channel::invite(Client &client, Client &inviter)
{
	_invited.push_back(client.getNickname());
	sendMessage(inviter, "341 " + inviter.getIdentifier() + " " + client.getNickname() + " " + _name);
	sendMessage(client, ":" + inviter.getIdentifier() + " INVITE " + client.getNickname() + " " + _name);
}

void		Channel::kick(Client &client, Client &kicker, std::string reason)
{
	for (std::vector<std::string>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (*it == client.getNickname())
		{
			sendMessageToAll(":" + kicker.getIdentifier() + " KICK " + _name + " " + client.getNickname() + " :" + reason);
			this->_clients.erase(it);
			if (this->isOperator(client))
				this->removeOperator(client);
			return;
		}
	}
}

bool		Channel::isEmpty() const
{
	return (_clients.size() == 0);
}