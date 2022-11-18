/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:00:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/18 14:07:29 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include <string>

# include "Client.hpp"
# include "Channel.hpp"

void	sendErrNeedMoreParams(Client &receiver, std::string cmd);
void	sendErrCannotSendToChan(Client &sender, std::string channelName);
void	sendErrNoSuchNick(Client &sender, std::string target);
Channel	*testInChannelAndSendError(Client &receiver, std::string channelName, std::vector<Channel> &channels);
void	sendErrNotAnOperator(Client &sender);

#endif
