/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errNeedMoreParams.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:54:30 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/14 14:23:05 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void	sendErrNeedMoreParams(Client &receiver, std::string cmd)
{
	sendMessage(receiver, "461 " + receiver.getNickname() + " " + cmd + " :Not enough parameters");
}
