/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:17:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/10 14:28:59 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <poll.h>

class Client
{
    public:
        Client(int socket);
        Client(Client const & src);
        ~Client(void);

        Client & operator=(Client const & rhs);

    private:
        Client(void);

        int             _socket;
        struct pollfd   _pollfd;
};

#endif