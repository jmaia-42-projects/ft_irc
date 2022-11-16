/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:14:35 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 18:06:06 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include "colors.hpp"
#include <unistd.h>

void    executeKill(Message &message, std::vector<Client> &clients)
{
	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), "KILL");
	else
    {
        if (!message.getSender().isOperator())
            sendErrNotAnOperator(message.getSender());
        else
        {
            for (size_t i = 0; i < clients.size(); i++)
            {
                if (clients[i].getNickname() == message.getParameters()[0])
                {
                    sendMessage(clients[i], ":" + message.getSender().getIdentifier() + " KILL " + clients[i].getNickname() + " :" + message.getParameters()[1]);
                    sendMessage(clients[i], "ERROR :Killed by " + message.getSender().getNickname() + " (" + message.getParameters()[1] + ")");
                    std::string identifier = clients[i].getIdentifier();
                    clients[i].disconnect(clients);
                    sendMessages(clients, ":" + identifier + " QUIT :Killed by " + message.getSender().getNickname() + " (" + message.getParameters()[1] + ")");
                    return ;
                }
            }
            sendMessage(message.getSender(), "401 " + message.getSender().getIdentifier() + " " + message.getParameters()[0] + " :No such nick/channel");
        }
    }
}