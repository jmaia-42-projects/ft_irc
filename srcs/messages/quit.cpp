/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/13 12:48:48 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    executeQuit(Message &message, std::vector<Client> &clients)
{
    if (message.getParameters().size() < 1)
        sendMessages(clients, ":" + message.getSender().getNickname() + " QUIT");
    else
    {
        sendMessages(clients, ":" + message.getSender().getNickname() + " QUIT :" + message.getParameters().at(0));
    }
}