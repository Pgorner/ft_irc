# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 15:14:57 by pgorner           #+#    #+#              #
#    Updated: 2023/08/20 17:18:40 by pgorner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors for the terminal
YELLOW = $(shell tput setaf 3)
GREEN = $(shell tput setaf 2)
RESET = $(shell tput sgr0)

NAME = ircserv
CC     = c++
AR     = ar rcs
RM     = rm -rf
OBJ_DIR = obj
LOG_DIR = logs
CFLAGS = -Wall -Werror -Wextra -std=c++98
LDFLAGS = -lncurses

# List of source files
SRC = src/main.cpp \
      src/utils/check.cpp \
      src/utils/error.cpp \
      src/utils/utils.cpp \
      src/utils/replies.cpp \
      src/server/server.cpp \
      src/server/startup.cpp \
      src/server/server_func.cpp \

# Convert source files to object files
OBJS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(NAME)

# Rule to create the object files in the OBJ_DIR
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "$(YELLOW)COMPILING $(RESET)$<$(YELLOW) ...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@


# Rule to create the OBJ_DIR directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Target for the final executable
$(NAME): $(OBJS)
	@echo "$(GREEN)COMPILED $(RESET)$(NAME)$(GREEN) successfully!$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

# Clean up object files and logs directory
clean:
	@$(RM) $(OBJ_DIR)

# Clean up object files, logs directory, and the executable
fclean: clean
	@$(RM) $(NAME) $(LOG_DIR)

# Target for installing irssi
irssi: brew install irssi

# Rule for testing
test: re
	@./$(NAME) 666 1234

# Target for recompiling everything
re: fclean all

.PHONY: all clean fclean irssi re
