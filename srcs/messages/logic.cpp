/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:55:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 15:18:15 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Message.hpp"

void    treatMessage(std::string message, Client &sender, std::vector<Client> &clients)
{
    (void)clients;

    std::vector<Message> messages;
    std::string::iterator separator1 = std::find(message.begin(), message.end(), '\n');
    messages.push_back(Message(sender, std::string(message.begin(), separator1)));
    while (separator1 != message.end())
    {
        std::string::iterator separator2 = std::find(separator1 + 1, message.end(), '\n');
        if(separator2 == separator1 + 1)
            break;
        messages.push_back(Message(sender, std::string(separator1 + 1, separator2)));
        separator1 = separator2;
    }
}