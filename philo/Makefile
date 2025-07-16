# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#              #
#    Updated: 2025/07/16 10:42:45 by kosakats         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./SRCS
OBJ_DIR = ./OBJS
INCLUDE_DIR = ./include
INCLUDES = -I $(INCLUDE_DIR)
LDFLAGS = -lpthread

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init/init.c \
       $(SRC_DIR)/thread/philosopher.c \
       $(SRC_DIR)/utils/ft_atoi.c \
       $(SRC_DIR)/thread/monitor.c \
       $(SRC_DIR)/routine/routine.c \
       $(SRC_DIR)/routine/eat/eat.c \
       $(SRC_DIR)/routine/forks/forks.c \
       $(SRC_DIR)/routine/sleep/sleep.c \
       $(SRC_DIR)/routine/think/think.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

all: prepare_dirs $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

prepare_dirs:
	mkdir -p $(sort $(dir $(OBJS)))

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

