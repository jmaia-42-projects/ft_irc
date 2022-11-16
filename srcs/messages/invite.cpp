/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:01 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 14:39:29 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executeInvite(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), "INVITE");
	else
	{
		Channel	*channel = testInChannelAndSendError(message.getSender(), message.getParameters().at(1), channels);
		if (channel != NULL)
		{
			if (channel->isOperator(message.getSender()))
			{
				for (size_t i = 0; i < clients.size(); i++)
				{
					if (clients[i].getNickname() == message.getParameters().at(0))
					{
						if (channel->isMember(clients[i]))
							sendMessage(message.getSender(), "443 " + message.getSender().getIdentifier() + " " + message.getParameters().at(0) + " " + message.getParameters().at(1) + " :is already on channel");
						else
							channel->invite(clients[i], message.getSender());
						return ;
					}   
				}
				sendMessage(message.getSender(), "401 " + message.getSender().getIdentifier() + " " + message.getParameters().at(0) + " :No such nickname");
			}
			else
				sendMessage(message.getSender(), "482 " + message.getParameters().at(0) + " :You're not channel operator");
		}
	}
}