/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:18:17 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 12:50:01 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "messages.hpp"

Channel::Channel(): _name(""), _topic("") {}

Channel::Channel(std::string name, Client &client): _name(name), _topic("")
{
    this->addOperator(client);
    this->addMember(client);
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
    }
    return *this;
}

bool        Channel::isMember(Client & client) const
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i].getId() == client.getId())
            return true;
    }
    return false;
}
void        Channel::addMember(Client & client)
{
    if (!this->isMember(client))
    {
        this->_clients.push_back(client);
        sendMessages(_clients, ":" + client.getNickname() + " JOIN " + _name);
        this->sendTopic(client);
        this->sendUserList(client);
    }
}
void        Channel::removeMember(Client & client, std::string reason)
{
    for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
        if (it->getId() == client.getId())
        {
            sendMessages(_clients, ":" + it->getNickname() + " PART " + _name + (reason == "" ? "" : " :") + reason);
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
        if (_operators[i].getId() == client.getId())
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
void        Channel::setTopic(std::string topic) { this->_topic = topic; }
void    Channel::sendTopic(Client &client) const
{
    if (_topic != "")
        sendMessage(client, "332 " + client.getNickname() + " " + _name + " :" + _topic);
}

void    Channel::sendUserList(Client &client) const
{
    std::string userList = "";
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (i != 0)
            userList += " ";
        if (this->isOperator(_clients.at(i)))
            userList += "@";
        userList += _clients.at(i).getNickname();
    }
    sendMessage(client, "353 " + client.getNickname() + " = " + _name + " :" + userList);
    sendMessage(client, "366 " + client.getNickname() + " " + _name + " :End of /NAMES list");
}