/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:06:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 17:44:45 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

void    sendMessage(Client &receiver, std::string text);
void    sendMessages(std::vector<Client> &clients, std::string text);

void    executeNick(Message &message, std::vector<Client> &clients)
{
    (void)clients;
    if (message.getParameters().size() < 1)
        sendMessage(message.getSender(), "431 NICK :Not enough parameters");
    else
    {
        for (size_t i = 0; i < clients.size(); i++)
        {
            if (clients[i].getNickname() == message.getParameters()[0])
            {
                sendMessage(message.getSender(), "433 NICK :Nickname is already in use");
                return ;
            }
        }
        std::string oldNickname = message.getSender().getNickname();
        message.getSender().setNickname(message.getParameters().at(0));
        if (oldNickname != "")
            sendMessages(clients, oldNickname + " NICK " + message.getParameters().at(0));
    }
}