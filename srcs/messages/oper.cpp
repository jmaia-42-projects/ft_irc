/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:31:15 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 16:35:32 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include <map>

void    executeOper(Message &message, std::vector<Client> &clients)
{
	std::map<std::string, std::string> operators;
	operators["norminet"] = "ViveLePoisson";
	
	(void)clients;
	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), "OPER");
	else
	{
		if (operators.find(message.getParameters()[0]) != operators.end())
		{
			if (operators[message.getParameters()[0]] == message.getParameters()[1])
			{
				message.getSender().setOperator();
				sendMessage(message.getSender(), "381 " + message.getSender().getIdentifier() + " :You are now an IRC operator");
			}
			else
				sendMessage(message.getSender(), "464 " + message.getSender().getIdentifier() + " :Password incorrect");
		}
		else
			sendMessage(message.getSender(), "491 " + message.getSender().getIdentifier() + " :No O-lines for your host");
	}
}