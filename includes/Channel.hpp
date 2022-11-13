/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:14:50 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/13 17:45:55 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>
# include "Client.hpp"

class Channel
{
    public:
        Channel(std::string name, Client &client);
        Channel(const Channel & src);
        ~Channel();

        Channel & operator=(const Channel & rhs);

        bool        isMember(Client & client);
        void        addMember(Client & client);
        void        removeMember(Client & client);
        bool        isOperator(Client & client);
        void        addOperator(Client & client);
        void        removeOperator(Client & client);
        std::string getName() const;
        std::string getTopic() const;
        void        setTopic(std::string topic);

        static bool isChannelNameValid(std::string name);

    private:
        Channel();
        std::vector<Client> _clients;
        std::vector<Client> _operators;
        std::string _name;
        std::string _topic;

};

#endif