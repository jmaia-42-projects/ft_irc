/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:46:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 11:10:48 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIV_MSG_HPP
# define PRIV_MSG_HPP

# include <string>
# include <vector>

# include "Message.hpp"

class	PrivMsg
{
	private:
		std::vector<string>	_targets;
		std::string			_message;

		PrivMsg(void);
	public:
		PrivMsg(Message &message);
		~PrivMsg(void);
		PrivMsg(const PrivMsg &obj);
		PrivMsg	&operator=(const PrivMsg &obj);

		std::vector<string>	getTargets(void);
		std::string			getText(void);
}

#endif
