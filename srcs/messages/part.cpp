/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 18:36:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executePart(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "PART");
	else
	{
		if (!Channel::isChannelNameValid(message.getParameters().at(0)))
			sendMessage(message.getSender(), "476 " + message.getParameters().at(0) + " :Bad channel name");
		else
		{
			Channel	*channel = testInChannelAndSendError(message.getSender(), message.getParameters().at(0), channels);
			if (channel != NULL)
			{
				if (message.getParameters().size() == 1)
					channel->removeMember(message.getSender());
				else
					channel->removeMember(message.getSender(), message.getParameters().at(1));
			}
		}
	}
}