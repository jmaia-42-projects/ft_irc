/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:43:59 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/17 12:46:18 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.hpp"
#include "status.hpp"

void    sigintHandler(int sig)
{
    (void)sig;
    std::cout << "\r";
    gStatus = 0;
}