/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:00:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/14 14:22:42 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICAL_REPLIES_HPP
# define NUMERICAL_REPLIES_HPP

# include <string>

# include "Client.hpp"

void	sendErrNeedMoreParams(Client &receiver, std::string cmd);

#endif
