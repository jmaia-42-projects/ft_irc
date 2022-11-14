/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:06:14 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/14 14:34:15 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>

int	checkArgsValidity(int ac, char **av);
int	checkArgsValidityAndPrintError(int ac, char **av);
int	parseArgs(int ac, char **av, unsigned short &port, std::string &password);

#endif
