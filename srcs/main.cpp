/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:50 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/08 22:12:38 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>

#include "parser.hpp"

int	main(int ac, char **av)
{
	int	err;

	err = check_args_validity(ac, av);
	if (err)
		return (err);
}
