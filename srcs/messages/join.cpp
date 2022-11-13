/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/13 17:46:27 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    executeJoin(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendMessage(message.getSender(), "461 " + message.getSender().getNickname() + " JOIN :Not enough parameters");
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
					channels.at(i).addMember(message.getSender());
					return ;
				}
			}
			channels.push_back(Channel(message.getParameters().at(0), message.getSender()));
		}
	}
}