# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 14:06:32 by ahamdy            #+#    #+#              #
#    Updated: 2022/06/02 11:40:14 by ahamdy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror -lreadline

SRCS = parser.c error_handling.c allocate_memory.c ft_strncmp.c here_doc.c io_utils.c main.c \
		parsing_utils.c split.c  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c io_redirections.c

NAME = minishell

LIBFT = libft/libft.a

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS)  $(SRCS)  libft/libft.a  -o minishell

$(LIBFT):
	make -C libft/

clean :
	make clean -C libft/

fclean : clean
	rm -f $(NAME)
	rm -rf libft/libft.a

re : fclean all

.PHONY : all clean fclean bonus re