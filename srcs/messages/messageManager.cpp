/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messageManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:55:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/13 12:49:28 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void executeMessage(Message &message, std::vector<Client> &clients)
{
    if (message.getCommand() == "PASS")
        executePass(message, clients);
    else
    {
        if (message.getSender().hasGivedPassword())
        {
            if (message.getCommand() == "NICK")
                executeNick(message, clients);
            if (message.getCommand() == "USER")
                executeUser(message, clients);
            if (message.getSender().isLogged())
            {
                if (message.getCommand() == "QUIT")
                    executeQuit(message, clients);
            }
        }
    }
}

void treatMessage(std::string message, Client &sender, std::vector<Client> &clients)
{
    (void)clients;

    std::vector<Message> messages;
    std::string::iterator separator1 = std::find(message.begin(), message.end(), '\n');
    messages.push_back(Message(sender, std::string(message.begin(), separator1)));
    while (separator1 != message.end())
    {
        std::string::iterator separator2 = std::find(separator1 + 1, message.end(), '\n');
        if (separator2 == separator1 + 1)
            break;
        messages.push_back(Message(sender, std::string(separator1 + 1, separator2)));
        separator1 = separator2;
    }
    for (size_t i = 0; i < messages.size(); i++)
        executeMessage(messages.at(i), clients);
}

void sendMessage(Client &receiver, std::string text)
{
    std::cout << "Sending message to client " << receiver.getId() << ": " << text << std::endl;
    text += "\n";
    send(receiver.getSocket(), text.c_str(), text.size(), 0);
}

void sendMessages(std::vector<Client> &clients, std::string text)
{
    for (size_t i = 0; i < clients.size(); i++)
        sendMessage(clients.at(i), text);
}
