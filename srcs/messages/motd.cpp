/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:28:30 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 16:13:55 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    executeMotd(Message &message)
{
	std::vector<std::string> motd;
	motd.push_back("Welcome to the Norminet IRC server !");
	motd.push_back("   _._     _,-'""`-._");
	motd.push_back("  (,-.`._,'(       |\\`-/|");
	motd.push_back("      `-.-' \\ )-`( , o o)");
	motd.push_back("            `-    \\`_`\"'-");

	sendMessage(message.getSender(), "375 " + message.getSender().getIdentifier() + " :- NormIrc Message of the day - ");
	for (std::vector<std::string>::iterator it = motd.begin(); it != motd.end(); ++it)
		sendMessage(message.getSender(), "372 " + message.getSender().getIdentifier() + " :" + *it);
	sendMessage(message.getSender(), "376 " + message.getSender().getIdentifier() + " :End of /MOTD command.");
}