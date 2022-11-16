/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:01 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 15:27:45 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executeKick(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), "KICK");
	else
	{
		Channel	*channel = testInChannelAndSendError(message.getSender(), message.getParameters().at(0), channels);
		if (channel != NULL)
		{
			if (channel->isOperator(message.getSender()))
			{
				for (size_t i = 0; i < clients.size(); i++)
				{
					if (clients[i].getNickname() == message.getParameters().at(1))
					{
						if (!channel->isMember(clients[i]))
							sendMessage(message.getSender(), "441 " + message.getSender().getIdentifier() + " " + message.getParameters().at(1) + " " + message.getParameters().at(0) + " :They aren't on that channel");
						else
							channel->kick(clients[i], message.getSender(), (message.getParameters().size() > 2 && message.getParameters().at(2) != "") ? message.getParameters().at(2) : "Kicked by an operator");
						return ;
					}   
				}
				sendMessage(message.getSender(), "401 " + message.getSender().getIdentifier() + " " + message.getParameters().at(1) + " :No such nickname");
			}
			else
				sendMessage(message.getSender(), "482 " + message.getParameters().at(0) + " :You're not channel operator");
		}
	}
}