/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:17:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/12 16:17:37 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <poll.h>
# include <string>

class Client
{
    public:
        Client(int socket);
        Client(Client const & src);
        ~Client(void);

        Client & operator=(Client const & rhs);

        struct pollfd getPollFd(void) const;
        int getSocket(void) const;
        int getId(void) const;

        void setNickname(std::string nickname);
        std::string getNickname(void) const;

    private:
        Client(void);

        static int      _globalId;

        int             _id;
        int             _socket;
        struct pollfd   _pollfd;
        std::string     _nickname;
};

#endif