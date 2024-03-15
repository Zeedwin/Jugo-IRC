NAME  = ircserv
CC    = c++
FLAGS = -Wextra -Wall -std=c++98 #-Werror
SRCS  = Channel.cpp \
		ChannelManager.cpp \
	    Message.cpp \
	    ServerCore.cpp\
	    User.cpp \
	    UserManager.cpp \
	    command_handler.cpp \
	    interface.cpp \
	    main.cpp
OBJS  = $(addprefix build/, $(SRCS:.cpp=.o))

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

./build/%.o: %.cpp
	mkdir -p ./build
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf ./build

fclean: clean
	rm ircserv

re:		clean all

.PHONY:	all clean fclean re

