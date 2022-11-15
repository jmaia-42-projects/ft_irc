/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messageManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:55:21 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 13:39:55 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "colors.hpp"

void executeMessage(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
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
				else if (message.getCommand() == "JOIN")
					executeJoin(message, clients, channels);
				else if (message.getCommand() == "PART")
					executePart(message, clients, channels);
				else if (message.getCommand() == "TOPIC")
					executeTopic(message, clients, channels);
			}
		}
	}
}

void treatMessage(std::string message, Client &sender, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	std::string text = sender.getRecvBuffer() + message;
	size_t pos;
	while ((pos = text.find("\r\n")) != std::string::npos)
	{
		std::string line = text.substr(0, pos);
		text = text.substr(pos + 2);
		Message message(sender, line);
		executeMessage(message, clients, channels);
	}
	sender.setRecvBuffer(text);
}

void sendMessage(Client &receiver, std::string text)
{
	std::cout << YELLOW << "> " << receiver.getId() << " | " << text << RESET << std::endl;
	text += "\n";
	send(receiver.getSocket(), text.c_str(), text.size(), 0);
}

void sendMessages(std::vector<Client> &clients, std::string text)
{
	for (size_t i = 0; i < clients.size(); i++)
		sendMessage(clients.at(i), text);
}
