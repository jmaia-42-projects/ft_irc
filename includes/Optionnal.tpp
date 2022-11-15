/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Optionnal.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:45:13 by jmaia             #+#    #+#             */
/*   Updated: 2022/11/15 15:26:50 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

template<typename T>
Optionnal<T>::Optionnal(void) {}

template<typename T>
Optionnal<T>::Optionnal(T *ptr)
{
	this->_isValid = ptr != NULL;
	if (this->_isValid)
		this->_obj = *ptr;
}

template<typename T>
Optionnal<T>::~Optionnal(void) { }

template<typename T>
Optionnal<T>::Optionnal(Optionnal<T> const &obj)
{
	*this = obj;
}

template<typename T>
Optionnal<T>	&Optionnal<T>::operator=(Optionnal<T> const &obj)
{
	this->_obj = obj._obj;
	this->_isValid = obj._isValid;
	return (*this);
}

template<typename T>
bool Optionnal<T>::isValid(void)
{
	return (this->_isValid);
}

template<typename T>
T Optionnal<T>::getObj(void)
{
	if (!this->_isValid)
		throw Optionnal<T>::ObjIsInvalidException();
	return (this->_obj);
}

template<typename T>
const char *Optionnal<T>::ObjIsInvalidException::what(void) const throw()
{
	return ("Obj is invalid !");
}
