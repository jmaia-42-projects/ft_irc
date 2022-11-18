/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errNoSuchNick.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:07:37 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/18 14:10:22 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void	sendErrNoSuchNick(Client &sender, std::string target)
{
	sendMessage(sender, "401 " + sender.getNickname() + " " + target + " : No such nick/channel");
}
