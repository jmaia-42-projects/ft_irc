/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 18:19:01 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

void    sendMessage(Client &receiver, std::string text);
void    sendMessages(std::vector<Client> &clients, std::string text);

void    executePass(Message &message, std::vector<Client> &clients)
{
    (void)clients;
    if (message.getParameters().size() < 1)
        sendMessage(message.getSender(), "461 USER :Not enough parameters");
    else
    {
        if (message.getSender().isLogged())
            sendMessage(message.getSender(), "462 USER :You are already logged in");
        else
        {
            if (message.getParameters().at(0) == "motdepasse")
                message.getSender().givePassword();
            else
                sendMessage(message.getSender(), "464 PASS :Password incorrect");
        }
    }
}