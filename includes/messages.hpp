/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:57 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 15:59:31 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_HPP
# define MESSAGES_HPP

# include <vector>
# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include "Client.hpp"
# include "Channel.hpp"
# include "Message.hpp"
# include "Channel.hpp"

void    sendMessage(Client &receiver, std::string text);
void    sendMessages(std::vector<Client> &clients, std::string text);
void    executeNick(Message &message, std::vector<Client> &clients);
void    executeUser(Message &message, std::vector<Client> &clients);
void    executePass(Message &message, std::vector<Client> &clients);
void    executeQuit(Message &message, std::vector<Client> &clients);
void    executeJoin(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executePart(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executeTopic(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executeMode(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executePrivMsg(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executeInvite(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executeKick(Message &message, std::vector<Client> &clients, std::vector<Channel> &channels);
void    executePing(Message &message, std::vector<Client> &clients);

#endif
