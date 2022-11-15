/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageReceiver.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:59:31 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 16:20:58 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_RECEIVER_HPP
# define MESSAGE_RECEIVER_HPP

# include <string>

class Client;

class	MessageReceiver
{
	public:
		virtual ~MessageReceiver(void){};
		virtual void receiveMessage(std::string message, Client &sender) = 0;
		virtual std::string	getName(void) = 0;
};

#endif
