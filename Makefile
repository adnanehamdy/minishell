# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 14:06:32 by ahamdy            #+#    #+#              #
#    Updated: 2022/06/21 22:39:32 by nelidris         ###   ########.fr        #
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
			$(EXEC_PATH)/builtin_cmds/unset_cmd.c \
			$(EXEC_PATH)/env_handler.c $(EXEC_PATH)/builtin_exec.c $(EXEC_PATH)/exec_proc.c \
			$(EXEC_PATH)/ptrlen.c

MAIN_SRCS = main.c

NAME = minishell

LIBFT = libft/libft.a

GREEN = "\033[0;32m"

YELLOW = "\033[0;33m"

BLUE = "\033[0;34m"

PURPLE = "\033[0;35m"

ENDCOLOR = "\033[0;37m"

all : $(NAME) | footer

header:
	@echo
	@echo $(PURPLE)"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "$(ENDCOLOR)
	@echo $(PURPLE)"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "$(ENDCOLOR)
	@echo $(PURPLE)"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "$(ENDCOLOR)
	@echo $(PURPLE)"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "$(ENDCOLOR)
	@echo $(PURPLE)"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"$(ENDCOLOR)
	@echo $(PURPLE)"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"$(ENDCOLOR)
	@echo

footer:
	@echo $(BLUE)"---> type "$(PURPLE)"./minishell"$(BLUE)" to start the program."$(ENDCOLOR)

$(NAME) :  $(PARS_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(LIBFT) $(GNL) | header
	@echo $(BLUE)"--------------------------- $(NAME) ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Compiling src files..."$(ENDCOLOR)
	@$(CC) $(CFLAGS) $(PARS_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(GNL) $(LIBFT) -o minishell
	@echo $(GREEN)"---> All files have been compiled successfully!"$(ENDCOLOR)							
	

$(LIBFT): | header
	@echo $(BLUE)"--------------------------- $(LIBFT) ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Compiling Libft files..."$(ENDCOLOR)
	@make -C libft > /dev/null
	@echo $(GREEN)"---> Libft has been compiled successfully!"$(ENDCOLOR)

clean : | header
	@echo $(BLUE)"--------------------------- clean ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Cleaning libft..."$(ENDCOLOR)
	@make fclean -C libft/ > /dev/null
	@echo $(GREEN)"---> Libft has been cleaned successfully!"$(ENDCOLOR)
	
fclean :  clean | header
	@echo $(BLUE)"--------------------------- fclean ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Cleaning minishell..."$(ENDCOLOR)
	@rm -f $(NAME) > /dev/null
	@echo $(GREEN)"---> minishell has been cleaned successfully!"$(ENDCOLOR)

re : fclean all

.PHONY : all clean fclean bonus re