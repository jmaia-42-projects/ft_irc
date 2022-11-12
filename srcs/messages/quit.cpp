/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 18:46:00 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

void    sendMessage(Client &receiver, std::string text);
void    sendMessages(std::vector<Client> &clients, std::string text);

void    executeQuit(Message &message, std::vector<Client> &clients)
{
    if (message.getParameters().size() < 1)
        sendMessages(clients, ":" + message.getSender().getNickname() + " QUIT");
    else
    {
        sendMessages(clients, ":" + message.getSender().getNickname() + " QUIT :" + message.getParameters().at(0));
    }
}