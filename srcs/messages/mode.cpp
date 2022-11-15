/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:01 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 15:54:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include "ModeModificator.hpp"

static void    modeOnChannel(Message &message, std::vector<Channel> &channels)
{
	if (message.getParameters().size() > 1)
	{
		Channel	*channel = testInChannelAndSendError(message.getSender(), message.getParameters().at(0), channels);
		if (channel != NULL)
		{
			std::vector<ModeModificatior> modeModificators = ModeModificatior::getModeModificators(message.getParameters(), 1, message.getSender());
			if (channel->isOperator(message.getSender()))
			{
				for (size_t i = 0; i < modeModificators.size(); i++)
					channel->changeMode(modeModificators.at(i), message.getSender());
			}
			else
				sendMessage(message.getSender(), "482 " + message.getParameters().at(0) + " :You're not channel operator");
		}
	}
}

void    executeMode(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	(void)clients;
	if (message.getParameters().size() < 1)
		sendErrNeedMoreParams(message.getSender(), "MODE");
	else
	{
		if (message.getParameters().at(0)[0] == '#')
			modeOnChannel(message, channels);
	}
}