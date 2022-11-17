/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:37:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/17 13:51:40 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    sendMessage(int socket, std::string msg)
{
    msg += "\r\n";
    send(socket, msg.c_str(), msg.length(), 0);
}

void    treatMessage(std::string msg, int socket)
{
    std::cout << msg << std::endl;
}

void    startRoutine(int socket)
{
    std::string msg;
    while(1)
    {
        char buffer[1024];
        bzero(buffer, 1024);
        int readed = read(socket, buffer, 1023);
        if(readed < 0)
        {
            std::cout << "Error reading from socket" << std::endl;
            break;
        }
        if (readed == 0)
        {
            std::cout << "Connection closed" << std::endl;
            break;
        }
        msg += std::string(buffer, readed);
        while (msg.find("\n") != std::string::npos)
        {
            treatMessage(msg.substr(0, msg.find("\n")), socket);
            msg = msg.substr(msg.find("\n") + 1);
        }
    }
}