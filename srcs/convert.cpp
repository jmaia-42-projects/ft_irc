/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:07:55 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/10 11:50:31 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "convert.hpp"

int	toInt(std::string str)
{
	std::stringstream	ss(str);
	int					nbr;

	ss >> nbr;
	return (nbr);
}

bool isNumber(std::string rawNumber)
{
	for (std::string::iterator it = rawNumber.begin(); it != rawNumber.end(); it++)
		if (!isdigit(*it))
			return (false);
	return (true);
}

