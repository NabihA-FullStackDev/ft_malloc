#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabihali <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 04:19:55 by nabihali          #+#    #+#              #
#    Updated: 2021/12/02 02:36:05 by nabihali         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	libft_malloc_

HOST		=	$(shell hostname)

CC	 		=	gcc

CFLAG		+=	-g -Wall -Wextra -Werror

FLAG_SRC	=	-c -fPIC

FLAG_LIB	=	-shared -o

SRC			=	ft_malloc.c	\
				ft_free.c	\
				ft_realloc.c \
				ft_print.c \
				heap_func.c \
				spot_locator.c \
				block_func.c

#				ft_calloc.c \

SRC_EXEC	=	main.c

OBJ			=	$(SRC:.c=.o)

OBJ_EXEC	=	$(SRC_EXEC:.c=.o)

.PHONY:		all

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) $(CFLAG) $(FLAG_LIB) $(NAME)$(HOST).so

%.o:		%.c
			$(CC) $(FLAG_SRC) $^ -o $@

exec:		$(OBJ) $(OBJ_EXEC)
			$(CC) $(OBJ) $(OBJ_EXEC) -o exec_test

clean:
			rm -f $(OBJ) $(OBJ_EXEC)

fclean:		clean
			rm -f $(NAME)$(HOST).so
			rm -f exec_test

re:			fclean all