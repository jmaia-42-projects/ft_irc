/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:06:14 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/17 13:25:46 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>

int	checkArgsValidity(int ac, char **av);
int	checkArgsValidityAndPrintError(int ac, char **av);
int	parseArgs(int ac, char **av, std::string &address, unsigned short &port, std::string &password);

#endif
