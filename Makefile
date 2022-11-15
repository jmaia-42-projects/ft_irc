NAME		=	ircserv

SRCS		=	main.cpp \
				poll.cpp \
				PrivMsg.cpp \
				$(addprefix messages/, \
					messageManager.cpp \
					nick.cpp \
					user.cpp \
					pass.cpp \
					privMsg.cpp \
					quit.cpp \
					$(addprefix numeric_replies/, \
						errNeedMoreParams.cpp \
					) \
				) \
				$(addprefix classes/, \
					Client.cpp \
					Message.cpp \
				) \
				$(addprefix parser/, \
					checkArgsValidity.cpp \
					parseArgs.cpp \
				) \
				convert.cpp \
				initSocket.cpp

_OBJS		=	${SRCS:.cpp=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

INCLUDE		=	-I includes/

CXX			=	c++
CXXFLAGS	=   -Wall -Wextra -Werror -std=c++98

#CXX			=	bash gfilt
CXXFLAGS	+=	-fdiagnostics-color=always 

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

.PHONY	:	all clean fclean re
