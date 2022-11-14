/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 14:34:44 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    executePart(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendMessage(message.getSender(), "461 " + message.getSender().getNickname() + " PART :Not enough parameters");
	else
	{
		if (!Channel::isChannelNameValid(message.getParameters().at(0)))
			sendMessage(message.getSender(), "476 " + message.getParameters().at(0) + " :Bad channel name");
		else
		{
			for (size_t i = 0; i < channels.size(); i++)
			{
				if (channels.at(i).getName() == message.getParameters().at(0))
				{
					if (channels.at(i).isMember(message.getSender()))
					{
						if (message.getParameters().size() == 1)
							channels.at(i).removeMember(message.getSender());
						else
							channels.at(i).removeMember(message.getSender(), message.getParameters().at(1));
					}
					else
						sendMessage(message.getSender(), "442 " + message.getSender().getNickname() + " " + message.getParameters().at(0) + " :You're not on that channel");
					return ;
				}
			}
			sendMessage(message.getSender(), "403 " + message.getSender().getNickname() + " " + message.getParameters().at(0) + " :No such channel");
		}
	}
}