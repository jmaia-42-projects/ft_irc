/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errNeedToBeInChannel.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:54:30 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/14 18:38:37 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

Channel	*testInChannelAndSendError(Client &receiver, std::string channelName, std::vector<Channel> &channels)
{
	if (!Channel::isChannelNameValid(channelName))
	{
		sendMessage(receiver, "476 " + channelName + " :Bad channel name");
		return NULL;
	}
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels.at(i).getName() == channelName)
		{
			if (channels.at(i).isMember(receiver))
				return &(channels.at(i));
			else
				sendMessage(receiver, "442 " + receiver.getNickname() + " " + channelName + " :You're not on that channel");
            return NULL;
		}
	}
	sendMessage(receiver, "403 " + receiver.getNickname() + " " + channelName + " :No such channel");
    return NULL;
}
