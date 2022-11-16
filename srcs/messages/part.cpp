/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 15:50:15 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include "colors.hpp"

void    executePart(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "PART");
	else
	{
		Channel	*channel = testInChannelAndSendError(message.getSender(), message.getParameters().at(0), channels);
		if (channel != NULL)
		{
			if (message.getParameters().size() == 1)
				channel->removeMember(message.getSender());
			else
				channel->removeMember(message.getSender(), message.getParameters().at(1));
			if (channel->isEmpty())
			{
				for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
				{
					if (it->getName() == channel->getName())
					{
						channels.erase(it);
						std::cout << BLUE << "Channel " << it->getName() << " was deleted" << RESET << std::endl;
						break;
					}
				}
			}
		}
	}
}