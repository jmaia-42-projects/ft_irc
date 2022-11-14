/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:33:10 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 14:33:59 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "Client.hpp"
# include <string>
# include <vector>
# include <algorithm>
# include <iostream>

class Message
{
	public:
		Message(Client &sender, std::string originalMessage);
		Message(Message const & src);
		~Message();

		Message &		operator=(Message const & rhs);

		Client &        getSender() const;
		std::string     getOriginalMessage() const;
		std::string     getCommand() const;
		std::vector<std::string>    getParameters() const;

	private:
		Client                      &_sender;
		std::string                 _originalMessage;
		std::string                 _command;
		std::vector<std::string>    _parameters;
};

#endif