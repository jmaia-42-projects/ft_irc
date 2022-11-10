/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:18:09 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/10 14:28:47 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void): _socket(-1)
{
}

Client::Client(int socket): _socket(socket)
{
    _pollfd.fd = socket;
    _pollfd.events = POLLIN + POLLOUT;
}

Client::Client(Client const & src)
{
    *this = src;
}

Client::~Client(void)
{
}

Client & Client::operator=(Client const & rhs)
{
    if (this != &rhs)
    {
    }
    return *this;
}