/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:50:19 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 18:35:53 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_HPP
# define POLL_HPP

# define POLL_SIZE 1024
# define REVC_BUFFER 4096

# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <poll.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <vector>
# include <iostream>
# include "Client.hpp"
# include "Channel.hpp"
# include "status.hpp"

void    treatMessage(std::string message, Client &sender, std::vector<Client> &clients, std::vector<Channel> &channels);

#endif