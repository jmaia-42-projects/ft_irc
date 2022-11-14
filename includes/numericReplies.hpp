/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:00:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/14 18:35:18 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICAL_REPLIES_HPP
# define NUMERICAL_REPLIES_HPP

# include <string>

# include "Client.hpp"

void	sendErrNeedMoreParams(Client &receiver, std::string cmd);
Channel	*testInChannelAndSendError(Client &receiver, std::string channelName, std::vector<Channel> &channels);

#endif
