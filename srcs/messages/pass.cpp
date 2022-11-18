/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/18 13:36:59 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include "colors.hpp"

void    executePass(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels, std::string password)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "PASS");
	else
	{
		if (message.getSender().isLogged())
			sendMessage(message.getSender(), "462 USER :You are already logged in");
		else
		{
			if (message.getParameters().at(0) == password)
				message.getSender().givePassword();
			else
			{
				sendMessage(message.getSender(), "464 PASS :Password incorrect");
				sendMessage(message.getSender(), "ERROR :Password incorrect");
                message.getSender().disconnect(clients, channels);
			}
		}
	}
}
