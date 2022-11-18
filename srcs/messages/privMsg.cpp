/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:09:49 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/18 14:13:03 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

#include "Channel.hpp"
#include "messages.hpp"
#include "numericReplies.hpp"
#include "PrivMsg.hpp"

static void	checkAllValid(PrivMsg &privMsg, std::vector<MessageReceiver *> targets, Client &client);
static std::vector<MessageReceiver *>	getTargets(PrivMsg privMsg, std::vector<Client> &clients, std::vector<Channel> &channels, Client &sender);
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
	targets = getTargets(optPrivMsg.getObj(), clients, channels, message.getSender());
	for (std::vector<MessageReceiver *>::iterator it = targets.begin(); it != targets.end(); it++)
		sendPrivMsg(*it, message.getSender(), message.getOriginalMessage());
}

static std::vector<MessageReceiver *>	getTargets(PrivMsg privMsg, std::vector<Client> &clients, std::vector<Channel> &channels, Client &sender)
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
	checkAllValid(privMsg, targets, sender);
	return (targets);
}

static void	checkAllValid(PrivMsg &privMsg, std::vector<MessageReceiver *> targets, Client &sender)
{
	for (std::vector<std::string>::iterator it = privMsg.getTargets().begin(); it != privMsg.getTargets().end(); it++)
	{
		bool	found = false;

		for (std::vector<MessageReceiver *>::iterator it2 = targets.begin(); it2 != targets.end() && !found; it2++)
		{
			if (*it == (*it2)->getName())
				found = true;
		}
		if (!found)
			sendErrNoSuchNick(sender, *it);
	}
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
