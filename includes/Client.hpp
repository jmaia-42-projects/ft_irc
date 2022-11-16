/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:17:36 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/16 18:04:08 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <poll.h>
# include <string>
# include <vector>

# include "MessageReceiver.hpp"

class Client:	public MessageReceiver
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
		std::string	getRecvBuffer(void) const;
		void	setRecvBuffer(std::string buffer);
		std::string	getIdentifier(void) const;
		void	disconnect(std::vector<Client> &clients);
		bool	isOperator(void) const;
		void	setOperator(void);

		void receiveMessage(std::string message, Client &sender);
		std::string getName(void);

		bool	operator==(Client const &obj);

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
		std::string		_recvBuffer;
		bool			_operator;
};

#endif
