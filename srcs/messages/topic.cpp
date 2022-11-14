/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 18:44:21 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void    executeTopic(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 2)
		sendErrNeedMoreParams(message.getSender(), "PART");
	else
	{
		Channel	*channel = testInChannelAndSendError(message.getSender(), message.getParameters().at(0), channels);
		if (channel != NULL)
            channel->setTopic(message.getParameters().at(1), message.getSender());
	}
}