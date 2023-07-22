# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 15:14:57 by pgorner           #+#    #+#              #
#    Updated: 2023/07/21 19:41:05 by pgorner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗
#	████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝
#	██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗
#	██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝
#	██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗
#	╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝

NAME = ircserv
CC		 = c++
CFLAGS   = -Wall -Werror -Wextra -std=c++98 -lncurses
AR		 = ar rcs
RM		 = rm -rf

SRC =	main.cpp				\
		src/utils/check.cpp		\
		src/utils/error.cpp		\
		src/utils/utils.cpp		\
		src/server/server.cpp	\


OBJS =		$(SRC:.cpp=.o)


$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all :		$(NAME)

clean :
		$(RM) $(OBJS)

fclean :	clean
			@$(RM) $(NAME)

re :		fclean all
