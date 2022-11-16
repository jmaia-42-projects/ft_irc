/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:14:35 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 18:43:53 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"
#include "numericReplies.hpp"
#include "status.hpp"

void    executeRestart(Message &message)
{
    if (!message.getSender().isOperator())
        sendErrNotAnOperator(message.getSender());
    else
        gStatus = 2;
}