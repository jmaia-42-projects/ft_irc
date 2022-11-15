/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeModificator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:23:46 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/15 15:04:18 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeModificator.hpp"
#include "messages.hpp"

ModeModificatior::ModeModificatior(){}

ModeModificatior::ModeModificatior(char mode, bool function, std::string param)
{
	_mode = mode;
	_function = function;
	_param = param;
}

ModeModificatior::ModeModificatior(const ModeModificatior & src)
{
	*this = src;
}

ModeModificatior::~ModeModificatior(){}

ModeModificatior & ModeModificatior::operator=(const ModeModificatior & rhs)
{
	_mode = rhs.getMode();
	_function = rhs.activate();
	_param = rhs.getParameter();
	return *this;
}

char	ModeModificatior::getMode() const
{
	return _mode;
}
bool	ModeModificatior::activate() const
{
	return _function;
}
std::string	ModeModificatior::getParameter() const
{
	return _param;
}

static int isModeNeedAnArgument(char mode, bool function)
{
	switch (mode)
	{
		case 'i':
			return 0;
			break;
		case 't':
			return 0;
			break;
		case 'l':
			return function ? 1 : 0;
			break;
		case 'o':
			return 1;
			break;
		
		default:
			return -1;
			break;
	}
}

std::vector<ModeModificatior> ModeModificatior::getModeModificators(std::vector<std::string> parameters, size_t modificatorsStringIndex, Client &sender)
{
	std::vector<ModeModificatior> modeModificators;
	std::string modificatorsString = parameters[modificatorsStringIndex];
	bool function = modificatorsString[0] == '+';
	size_t argumentUsed = 0;
	for (size_t i =  1; i < modificatorsString.length(); i++)
	{
		if (modificatorsString[i] == '+' || modificatorsString[i] == '-')
			function = modificatorsString[i] == '+';
		else
		{
			int	needAnArgument = isModeNeedAnArgument(modificatorsString[i], function);
			if (needAnArgument == -1)
				sendMessage(sender, "501 " + sender.getIdentifier() + " :Unknown MODE flag");
			else
			{					
				if (!needAnArgument || parameters.size() > (modificatorsStringIndex + argumentUsed + 1))
					modeModificators.push_back(ModeModificatior(modificatorsString[i], function, needAnArgument ? parameters[modificatorsStringIndex + argumentUsed++ + 1] : ""));
			}
		}
	}
	return modeModificators;
}