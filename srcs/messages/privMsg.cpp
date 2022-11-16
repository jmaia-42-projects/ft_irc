/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:09:49 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/16 17:27:17 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

#include "Channel.hpp"
#include "messages.hpp"
#include "numericReplies.hpp"
#include "PrivMsg.hpp"

static std::vector<MessageReceiver *>	getTargets(PrivMsg privMsg, std::vector<Client> &clients, std::vector<Channel> &channels);
static bool	isMessageForMe(MessageReceiver *receiver, PrivMsg &privMsg);
static void								sendPrivMsg(MessageReceiver *target, Client &sender, std::string message);

template<typename T>
static T	*getPointer(T &obj);

void	executePrivMsg(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	Optionnal<PrivMsg>	optPrivMsg = PrivMsg::construct(message);
	std::vector<MessageReceiver *>	targets;

	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), message.getCommand());
	if (!optPrivMsg.isValid())
		return ;
	targets = getTargets(optPrivMsg.getObj(), clients, channels);
	for (std::vector<MessageReceiver *>::iterator it = targets.begin(); it != targets.end(); it++)
		sendPrivMsg(*it, message.getSender(), message.getOriginalMessage());
}

static std::vector<MessageReceiver *>	getTargets(PrivMsg privMsg, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	std::vector<MessageReceiver *>	targets;

	std::transform(clients.begin(), clients.end(), std::back_inserter(targets), getPointer<Client>);
	std::transform(channels.begin(), channels.end(), std::back_inserter(targets), getPointer<Channel>);
	for (std::vector<MessageReceiver *>::iterator it = targets.begin(); it != targets.end();)
	{
		if (!isMessageForMe(*it, privMsg))
			it = targets.erase(it);
		else
			it++;
	}
	return (targets);
}

template<typename T>
static T	*getPointer(T &obj)
{
	return (&obj);
}

static bool	isMessageForMe(MessageReceiver *receiver, PrivMsg &privMsg)
{
	return (find(privMsg.getTargets().begin(), privMsg.getTargets().end(), receiver->getName()) != privMsg.getTargets().end());
}

static void	sendPrivMsg(MessageReceiver *target, Client &sender, std::string message)
{
	target->receiveMessage(":" + sender.getNickname() + " " + message, sender);
}
