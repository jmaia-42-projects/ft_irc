/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:06:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 16:00:16 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executePing(Message &message, std::vector<Client> &clients)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "PING");
	else
        sendMessage(message.getSender(), "PONG :" + message.getParameters().at(0));
}