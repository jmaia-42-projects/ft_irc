/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/18 12:42:03 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executeJoin(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "JOIN");
	else
	{
		std::string channelNames = message.getParameters()[0];
		std::string::iterator firstSeparator = channelNames.begin();
		while (firstSeparator != channelNames.end())
		{
			if (*firstSeparator == ',')
				firstSeparator++;
			std::string::iterator secondSeparator = std::find(firstSeparator, channelNames.end(), ',');
			std::string channelName = std::string(firstSeparator, secondSeparator);
			std::cout << "trying to join channel " << channelName << "|" << std::endl;
			if (!Channel::isChannelNameValid(channelName))
				sendMessage(message.getSender(), "476 " + channelName + " :Bad channel name");
			else
			{
				bool	found = false;
				for (size_t i = 0; i < channels.size(); i++)
				{
					if (channels.at(i).getName() == channelName)
					{
						channels.at(i).addMember(&(message.getSender()));
						found = true;
						break;
					}
				}
				if (!found)
					channels.push_back(Channel(channelName, message.getSender(), clients));
			}
			firstSeparator = secondSeparator;
		}
	}
}