/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:17:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/14 14:33:22 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <poll.h>
# include <string>

class Client
{
	public:
		Client(int socket);
		Client(Client const & src);
		~Client(void);

		Client & operator=(Client const & rhs);

		struct pollfd getPollFd(void) const;
		int getSocket(void) const;
		int getId(void) const;

		void setNickname(std::string nickname);
		std::string getNickname(void) const;
		void setUsername(std::string username);
		std::string getUsername(void) const;
		void setRealname(std::string realname);
		std::string getRealname(void) const;
		void log(void);
		bool isLogged(void) const;
		void givePassword(void);
		bool hasGivedPassword(void) const;

	private:
		Client(void);

		static int      _globalId;

		int             _id;
		int             _socket;
		struct pollfd   _pollfd;
		bool            _givedPassword;
		std::string     _nickname;
		bool            _logged;
		std::string     _username;
		std::string     _realname;
};

#endif