# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 14:06:32 by ahamdy            #+#    #+#              #
#    Updated: 2022/06/16 14:38:05 by ahamdy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address -g

PARS_PATH = srcs/parsing

EXEC_PATH = srcs/executing

GNL = get_next_line/get_next_line.c

PARS_SRCS = $(PARS_PATH)/allocate_memory.c $(PARS_PATH)/error_handling.c \
			$(PARS_PATH)/find_path.c $(PARS_PATH)/here_doc.c \
			$(PARS_PATH)/io_redirections.c $(PARS_PATH)/io_utils.c \
			$(PARS_PATH)/parser.c $(PARS_PATH)/parsing_split.c \
			$(PARS_PATH)/parsing_utils.c $(PARS_PATH)/skip_alloc_utils.c \
			 $(PARS_PATH)/sub_alloc_mem.c

EXEC_SRCS = $(EXEC_PATH)/builtin_cmds/cd_cmd.c $(EXEC_PATH)/builtin_cmds/echo_cmd.c \
			$(EXEC_PATH)/builtin_cmds/env_cmd.c $(EXEC_PATH)/builtin_cmds/exit_cmd.c \
			$(EXEC_PATH)/builtin_cmds/export_cmd.c $(EXEC_PATH)/builtin_cmds/pwd_cmd.c \
			$(EXEC_PATH)/env_handler.c $(EXEC_PATH)/exec_proc.c $(EXEC_PATH)/ptrlen.c

MAIN_SRCS = main.c

NAME = minishell

BONUS =

LIBFT = libft/libft.a

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(PARS_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(PARS_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(GNL) $(LIBFT) -o minishell

$(LIBFT):
	make -C libft

clean :
	make fclean -C libft/

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean bonus re