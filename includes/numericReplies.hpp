/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:00:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 18:09:03 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# include <string>

# include "Client.hpp"

void	sendErrNeedMoreParams(Client &receiver, std::string cmd);
Channel	*testInChannelAndSendError(Client &receiver, std::string channelName, std::vector<Channel> &channels);

#endif
