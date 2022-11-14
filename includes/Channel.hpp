/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:14:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 18:44:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <map>
# include <string>

# include "Client.hpp"
# include "MessageReceiver.hpp"

class Channel:	public MessageReceiver
{
	public:
		Channel(std::string name, Client &client);
		Channel(const Channel & src);
		~Channel();

		Channel & operator=(const Channel & rhs);

		bool        isMember(Client & client) const;
		void        addMember(Client & client);
		void        removeMember(Client & client);
		void        removeMember(Client & client, std::string reason);
		bool        isOperator(Client & client) const;
		bool        isOperator(const Client & client) const;
		void        addOperator(Client & client);
		void        removeOperator(Client & client);
		std::string getName() const;
		std::string getTopic() const;
		void        setTopic(std::string topic, Client &modifier);
		void		receiveMessage(std::string message);

		static bool isChannelNameValid(std::string name);

	private:
		Channel();
		std::vector<Client> _clients;
		std::vector<Client> _operators;
		std::string _name;
		std::string _topic;
		std::map<char, unsigned int> _modes;

		void    sendTopic(Client &client) const;
		void    sendUserList(Client &client) const;

};

#endif