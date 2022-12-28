# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 14:46:50 by esalim            #+#    #+#              #
#    Updated: 2022/12/28 16:23:24 by esalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
SRC		=	src/pipex.c src/error.c src/pipex_utils.c src/error.c
OBJ		=	${SRC:.c=.o}
RM		=	rm -f

LIBFT	= libft
FT_PRINTF = ft_printf
MAKE	= make -C

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(MAKE) $(LIBFT)
	$(MAKE) $(FT_PRINTF)
	$(CC) $(CFLAGS) $^ libs/libft.a libs/libftprintf.a -o $@

run		: $(NAME)
	./$(NAME) infile "cat" "grep me" outfile

%.o		:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	$(MAKE) $(LIBFT) clean
	$(MAKE) $(FT_PRINTF) clean
	$(RM) $(OBJ)

fclean	:	clean
	$(MAKE) $(LIBFT) fclean
	$(MAKE) $(FT_PRINTF) fclean
	$(RM) $(NAME)

re		: fclean all
