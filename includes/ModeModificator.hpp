/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeModificator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:18:38 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 15:56:31 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEMODIFICATOR_HPP
# define MODEMODIFICATOR_HPP

# include <string>
# include <vector>
# include "Client.hpp"

class ModeModificatior
{
	public:
		ModeModificatior();
		ModeModificatior(char mode, bool function, std::string param);
		ModeModificatior(const ModeModificatior & src);
		~ModeModificatior();
		ModeModificatior & operator=(const ModeModificatior & rhs);

		char        getMode() const;
		bool        activate() const;
		std::string getParameter() const;

		static std::vector<ModeModificatior> getModeModificators(std::vector<std::string> parameters, size_t modificatorsStringIndex, Client &sender);

	private:
		char        _mode;
		bool        _function;
		std::string _param;
};

#endif