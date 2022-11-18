/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/18 13:24:39 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "PrivMsg.hpp"

static PrivMsgStatus getMessageValidity(Message &msg);
static std::vector<std::string>	split(std::string msg, char delim);

PrivMsg::PrivMsg(void) {}

PrivMsg::~PrivMsg(void) {}

PrivMsg::PrivMsg(const PrivMsg &obj)
{
	*this = obj;
}

PrivMsg	&PrivMsg::operator=(const PrivMsg &obj)
{
	this->_targets = obj._targets;
	this->_message = obj._message;
	return (*this);
}

Optionnal<PrivMsg>	PrivMsg::construct(Message &msg)
{
	PrivMsg	privMsg;

	if (getMessageValidity(msg) != SUCCESS)
		return (Optionnal<PrivMsg>(NULL));
	privMsg = parseMessage(msg);
	return (Optionnal<PrivMsg>(&privMsg));
}

static PrivMsgStatus getMessageValidity(Message &msg)
{
	std::vector<std::string> params;

	params = msg.getParameters();
	if (params.size() != 2)
		return (ERR_NEEDMOREPARAMS);
	return (SUCCESS);
}

PrivMsg	PrivMsg::parseMessage(Message &msg)
{
	PrivMsg	privMsg;

	privMsg._targets = split(msg.getParameters()[0], ',');
	privMsg._message = msg.getParameters()[1];
	return (privMsg);
}

static std::vector<std::string>	split(std::string msg, char delim)
{
	std::istringstream			splitter(msg);
	std::vector<std::string>	tokens;

	for (std::string token; std::getline(splitter, token, delim);)
		tokens.push_back(token);
	return (tokens);
}

std::vector<std::string>	&PrivMsg::getTargets(void)
{
	return (this->_targets);
}

std::string	&PrivMsg::getText(void)
{
	return (this->_message);
}
