/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:39:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 13:30:05 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    executeQuit(Message &message, std::vector<Client> &clients)
{
	message.getSender().disconnect();
	if (message.getParameters().size() < 1)
		sendMessages(clients, ":" + message.getSender().getNickname() + " QUIT");
	else
	{
		sendMessages(clients, ":" + message.getSender().getIdentifier() + " QUIT :" + message.getParameters().at(0));
	}
}