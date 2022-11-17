/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:21:59 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/17 13:46:04 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "messages.hpp"

int main(int ac, char **av)
{
    std::string address;
    unsigned short port;
    std::string password;

    if (parseArgs(ac, av, address, port, password))
        return (1);

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) 
        return (perror("socket"), 1);
    struct hostent *server = gethostbyname(address.c_str());
    if (server == NULL) {
       std::cerr << "No such host" << std::endl;
       return (1);
    }
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(clientSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        return (perror("connect"), 1);
    sendMessage(clientSocket, "PASS " + password);
    sendMessage(clientSocket, "NICK IRCbot");
    sendMessage(clientSocket, "USER IRCbot IRCbot IRCbot :IRC bot");
    startRoutine(clientSocket);
    close(clientSocket);
}