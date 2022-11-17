/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:21:59 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/17 13:29:27 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

int main(int ac, char **av)
{
    std::string adress;
    unsigned short port;
    std::string password;

    int err = parseArgs(ac, av, adress, port, password);
    if (err)
        return (err);
}