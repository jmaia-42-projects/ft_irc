/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errCannotSendToChan.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:35:06 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/16 14:38:33 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void	sendErrCannotSendToChan(Client &sender, std::string channelName)
{
	sendMessage(sender, "404 " + sender.getNickname() + " " + channelName + " : Cannot send to channel");
}
