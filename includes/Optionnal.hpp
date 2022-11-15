/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Optionnal.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:36:26 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 14:20:58 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONNAL_HPP
# define OPTIONNAL_HPP

template<typename T>
class	Optionnal
{
	private:
		T		_obj;
		bool	_isValid;

		Optionnal<T>(void);
	public:
		Optionnal<T>(T *ptr);
		~Optionnal<T>(void);
		Optionnal<T>(Optionnal<T> const &obj);

		Optionnal<T>	&operator=(Optionnal<T> const &obj);

		bool	isValid(void);
		T		getObj(void);
	
	class ObjIsInvalidException:	public std::exception
	{
		virtual const char * what(void) const throw();
	};
};

# include "Optionnal.tpp"

#endif
