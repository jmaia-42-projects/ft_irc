/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:09:49 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 12:55:00 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

#include "Channel.hpp"
#include "messages.hpp"
#include "numericReplies.hpp"
#include "PrivMsg.hpp"

static std::vector<MessageReceiver *>	getTargets(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
static bool	isMessageForMe(MessageReceiver *receiver, Message &message);
static void								sendPrivMsg(MessageReceiver *target, std::string sender, std::string message);

template<typename T>
static T	*getPointer(T &obj);

// Faire la gestion d'erreur directement dans executePrivMsg
// Instancer un PrivMsg pour ça
// Il faut encore remplir une fonction en bas
void	executePrivMsg(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	std::vector<MessageReceiver *>	targets;
	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), message.getCommand());
	targets = getTargets(message, clients, channels);
	for (std::vector<MessageReceiver *>::iterator it = targets.begin(); it != targets.end(); it++)
		sendPrivMsg(*it, message.getSender().getNickname(), message.getOriginalMessage());
}

static std::vector<MessageReceiver *>	getTargets(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	std::vector<MessageReceiver *>	targets;

	std::transform(clients.begin(), clients.end(), targets.end(), getPointer<Client>);
	std::transform(channels.begin(), channels.end(), targets.end(), getPointer<Channel>);
	for (std::vector<MessageReceiver *>::iterator it = targets.begin(); it != targets.end();)
	{
		if (!isMessageForMe(*it, message))
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

static bool	isMessageForMe(MessageReceiver *receiver, Message &message)
{
	(void) receiver;
	(void) message;
	return (true);
}

static void	sendPrivMsg(MessageReceiver *target, std::string sender, std::string message)
{
	target->receiveMessage(":" + sender + " " + message);
}
