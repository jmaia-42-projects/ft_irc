/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageReceiver.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:59:31 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/14 14:25:13 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_RECEIVER_HPP
# define MESSAGE_RECEIVER_HPP

# include <string>

class	MessageReceiver
{
	public:
		virtual ~MessageReceiver(void){};
		virtual void receiveMessage(std::string message) = 0;
};

#endif
