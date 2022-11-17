NAME		=	ircserv

SRCS		=	main.cpp \
				poll.cpp \
				signal.cpp \
				convert.cpp \
				initSocket.cpp \
				$(addprefix messages/, \
					$(addprefix numeric_replies/, \
						errCannotSendToChan.cpp \
						errNeedMoreParams.cpp \
						errNeedToBeInChannel.cpp \
						errNotAnOperator.cpp \
					) \
					messageManager.cpp \
					nick.cpp \
					user.cpp \
					pass.cpp \
					privMsg.cpp \
					quit.cpp \
					join.cpp \
					part.cpp \
					topic.cpp \
					mode.cpp \
					invite.cpp \
					kick.cpp \
					ping.cpp \
					motd.cpp \
					oper.cpp \
					kill.cpp \
					restart.cpp \
				) \
				$(addprefix classes/, \
					Client.cpp \
					Message.cpp \
					Channel.cpp \
					ModeModificator.cpp \
					PrivMsg.cpp \
				) \
				$(addprefix parser/, \
					checkArgsValidity.cpp \
					parseArgs.cpp \
				)

_OBJS		=	${SRCS:.cpp=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

CXX			=	clang++
CXXFLAGS	=   -Wall -Wextra -Werror -std=c++98
INCLUDE		=	-I includes/

all		:	$(NAME)

build/%.o	:	srcs/%.cpp
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CXX) ${CXXFLAGS} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

-include $(OBJS_DEPEND)

bonus: $(NAME)

clean	:	
	rm -Rf build/

fclean	:	clean
	rm -f ${NAME}

re		:	fclean ${NAME}

bonus	:	all
	make -C bot

.PHONY	:	all clean fclean re bonus
