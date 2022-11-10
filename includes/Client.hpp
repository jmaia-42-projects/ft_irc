/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:17:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/10 14:24:02 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

class Client
{
    public:
        Client(void);
        Client(int socket);
        Client(Client const & src);
        ~Client(void);

        Client & operator=(Client const & rhs);

    private:
        int _socket;
};

#endif