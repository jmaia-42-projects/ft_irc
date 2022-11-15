/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 14:30:26 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "PrivMsg.hpp"

static bool isMessageValid(Message &msg);
static bool areTargetsValid(std::string targets);
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

	if (!isMessageValid(msg))
		return (Optionnal<PrivMsg>(NULL));
	privMsg = parseMessage(msg);
	return (Optionnal<PrivMsg>(&privMsg));
}

static bool isMessageValid(Message &msg)
{
	std::vector<std::string> params;

	params = msg.getParameters();
	return (params.size() == 2 && areTargetsValid(params[0]));
}

static bool areTargetsValid(std::string targets)
{
	bool	isValid;

	isValid = false;
	for (std::string::iterator it = targets.begin(); it != targets.end(); it++)
	{
		if (!isValid && *it == ',')
			return (false);
		isValid = *it != ',';
		if (*it == ',')
			isValid = false;
		else
			isValid = true;
	}
	return (isValid);
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
