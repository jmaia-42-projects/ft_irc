/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 17:44:30 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

void    sendMessage(Client &receiver, std::string text);
void    sendMessages(std::vector<Client> &clients, std::string text);

void    executeUser(Message &message, std::vector<Client> &clients)
{
    (void)clients;
    if (message.getParameters().size() < 4)
        sendMessage(message.getSender(), "431 USER :Not enough parameters");
    else
    {
        if (message.getSender().isLogged())
            sendMessage(message.getSender(), "462 USER :You are already logged in");
        else
        {
            message.getSender().setUsername(message.getParameters().at(0));
            message.getSender().setRealname(message.getParameters().at(3));
            message.getSender().log();
            sendMessage(message.getSender(), "001 " + message.getSender().getNickname() + " :Welcome to the Internet Relay Network " + message.getSender().getNickname() + "!");
        }
    }
}