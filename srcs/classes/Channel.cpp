/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:18:17 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/13 17:22:16 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(): _name(""), _topic("")
{
}

Channel::Channel(std::string name): _name(name), _topic("")
{
}

Channel::Channel(const Channel & src)
{
    *this = src;
}

Channel::~Channel()
{
}

Channel & Channel::operator=(const Channel & rhs)
{
    if (this != &rhs)
    {
        this->_name = rhs._name;
        this->_topic = rhs._topic;
        this->_clients = rhs._clients;
        this->_operators = rhs._operators;
    }
    return *this;
}

bool        Channel::isMember(Client & client)
{
    for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
        if (it->getId() == client.getId())
            return true;
    }
    return false;
}
void        Channel::addMember(Client & client)
{
    if (!this->isMember(client))
        this->_clients.push_back(client);
}
void        Channel::removeMember(Client & client)
{
    for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
        if (it->getId() == client.getId())
        {
            this->_clients.erase(it);
            return;
        }
    }
}
bool        Channel::isOperator(Client & client)
{
    for (std::vector<Client>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
    {
        if (it->getId() == client.getId())
            return true;
    }
    return false;
}
void        Channel::addOperator(Client & client)
{
    if (!this->isOperator(client))
        this->_operators.push_back(client);
}
void        Channel::removeOperator(Client & client)
{
    for (std::vector<Client>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
    {
        if (it->getId() == client.getId())
        {
            this->_operators.erase(it);
            return;
        }
    }
}
std::string Channel::getName() const
{
    return this->_name;
}
std::string Channel::getTopic() const
{
    return this->_topic;
}
void        Channel::setTopic(std::string topic)
{
    this->_topic = topic;
}