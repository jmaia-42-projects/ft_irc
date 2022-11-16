/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errNotAnOperator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:35:06 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/16 17:17:33 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"

void	sendErrNotAnOperator(Client &sender)
{
	sendMessage(sender, "481 " + sender.getIdentifier() + " :Permission Denied- You're not an IRC operator");
}
