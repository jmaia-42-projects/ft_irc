/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:06:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/18 12:18:00 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executeNick(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "NICK");
	else
	{
		for (size_t i = 0; i < clients.size(); i++)
		{
			if (clients[i].getNickname() == message.getParameters()[0])
			{
				sendMessage(message.getSender(), "433 NICK :" + message.getParameters()[0]);
				return ;
			}
		}
		std::string oldNickname = message.getSender().getNickname();
		message.getSender().setNickname(message.getParameters().at(0));
		if (message.getSender().isLogged())
		{
			sendMessages(clients, ":" + oldNickname + " NICK " + message.getParameters().at(0));
			for (size_t i = 0; i < channels.size(); i++)
				channels[i].changeNickname(oldNickname, message.getParameters().at(0));
		}
		if (!message.getSender().isLogged() && message.getSender().getRealname() != "" && message.getSender().getUsername() != "")
		{
			message.getSender().log();
			sendMessage(message.getSender(), "001 " + message.getSender().getNickname() + " :Welcome to the Internet Relay Network " + message.getSender().getIdentifier() + "!");
			executeMotd(message);
		}
	}
}