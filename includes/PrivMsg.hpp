/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:46:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 12:39:30 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIV_MSG_HPP
# define PRIV_MSG_HPP

# include <string>
# include <vector>

# include "Message.hpp"
# include "Optionnal.hpp"

class	PrivMsg
{
	private:
		std::vector<std::string>	_targets;
		std::string					_message;

		PrivMsg(void);

		static PrivMsg	parseMessage(Message &message);
	public:
		~PrivMsg(void);
		PrivMsg(const PrivMsg &obj);
		PrivMsg	&operator=(const PrivMsg &obj);

		static Optionnal<PrivMsg>	construct(Message &msg);

		std::vector<std::string>	getTargets(void);
		std::string			getText(void);
	
	friend class Optionnal<PrivMsg>;
};

#endif
