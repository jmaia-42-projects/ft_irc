/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/17 12:37:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include "colors.hpp"

void    executePass(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
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
			if (message.getParameters().at(0) == "motdepasse")
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