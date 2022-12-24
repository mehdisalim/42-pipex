# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 14:46:50 by esalim            #+#    #+#              #
#    Updated: 2022/12/24 14:52:28 by esalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
# CFLAGS	=	-Wall -Werror -Wextra
SRC		=	main.c
OBJ		=	${SRC:.c=.o}

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^