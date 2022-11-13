/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initSocket.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:51:55 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/11 18:02:28 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SOCKET_HPP
# define INIT_SOCKET_HPP

int	initSocket(unsigned short port);
int	initSocketOrPrintError(unsigned short port);

#endif