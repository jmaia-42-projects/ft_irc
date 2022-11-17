/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:37:52 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/17 14:08:32 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.hpp"

void    sendMessage(int socket, std::string msg)
{
    msg += "\r\n";
    send(socket, msg.c_str(), msg.length(), 0);
}

void    receivePrivateMessage(std::string from, std::string msg, int socket)
{
    std::cout << "Private message from " << from << ": " << msg << std::endl;
    if(msg == "!ping")
        sendMessage(socket, "PRIVMSG " + from + " :pong");
}

void    treatMessage(std::string msg, int socket)
{
    if (msg[0] == ':')
        msg = msg.substr(1);
    std::vector<std::string> args;
    std::string::iterator separator1 = msg.begin() - 1;
	while (separator1 != msg.end())
	{
		std::string::iterator separator2 = std::find(separator1 + 1, msg.end(), ' ');
		std::string::iterator finalSeparator = std::find(separator1 + 1, msg.end(), ':');
		if (finalSeparator < separator2)
		{
			args.push_back(std::string(finalSeparator + 1, msg.end()));
			break;
		}
		args.push_back(std::string(separator1 + 1, separator2));
		separator1 = separator2;
	}
    if (args[0] == "001")
        std::cout << "Bot started!" << std::endl;
    if (args[0] == "ERROR")
    {
        close(socket);
        exit(1);
    }
    if (args.size() >= 4 && args[1] == "PRIVMSG")
        receivePrivateMessage(args[0], args[3], socket);
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