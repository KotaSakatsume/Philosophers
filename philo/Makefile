# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#              #
#    Updated: 2025/06/22 11:42:51 by kosakats         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for philo project

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
OBJ_DIR = ./obj
INCLUDE_DIR = ./include
INCLUDES = -I $(INCLUDE_DIR)
LDFLAGS = -lpthread

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       #$(SRC_DIR)/philosopher.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Build executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compile source files into objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything including the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
