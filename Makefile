NAME		=	ircserv

SRCS		=	main.cpp \
				poll.cpp \
				$(addprefix messages/, \
					logic.cpp \
					nick.cpp \
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

CXX			=	c++
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

.PHONY	:	all clean fclean re
