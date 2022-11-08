/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:07:55 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/08 22:14:20 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "convert.hpp"

int	to_int(std::string str)
{
	std::stringstream	ss(str);
	int					nbr;

	ss >> nbr;
	return (nbr);
}

bool is_number(std::string raw_number)
{
	for (std::string::iterator it = raw_number.begin(); it != raw_number.end(); it++)
		if (!isdigit(*it))
			return (false);
	return (true);
}

