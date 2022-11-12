/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:35:01 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 15:16:00 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(Client &sender, std::string originalMessage): _sender(sender), _originalMessage(originalMessage)
{
    if (_originalMessage[_originalMessage.size() - 1] == '\r')
        _originalMessage.erase(_originalMessage.size() - 1);
    std::string::iterator separator1 = std::find(_originalMessage.begin(), _originalMessage.end(), ' ');
    _command = std::string(_originalMessage.begin(), separator1);
    while (separator1 != _originalMessage.end())
    {
        std::string::iterator separator2 = std::find(separator1 + 1, _originalMessage.end(), ' ');
        std::string::iterator finalSeparator = std::find(separator1 + 1, _originalMessage.end(), ':');
        if (finalSeparator < separator2)
        {
            _parameters.push_back(std::string(finalSeparator + 1, _originalMessage.end()));
            break;
        }
        _parameters.push_back(std::string(separator1 + 1, separator2));
        separator1 = separator2;
    }
}

Message::Message(Message const & src): _sender(src._sender)
{
    *this = src;
}

Message::~Message()
{
}

Message &		Message::operator=(Message const & rhs)
{
    if (this != &rhs)
    {
        _sender = rhs._sender;
        _originalMessage = rhs._originalMessage;
        _command = rhs._command;
        _parameters = rhs._parameters;
    }
    return *this;
}

Client &        Message::getSender() const
{
    return _sender;
}
std::string     Message::getOriginalMessage() const
{
    return _originalMessage;
}
std::string     Message::getCommand() const
{
    return _command;
}
std::vector<std::string>    Message::getParameters() const
{
    return _parameters;
}