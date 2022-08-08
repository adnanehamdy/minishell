# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 14:06:32 by ahamdy            #+#    #+#              #
#    Updated: 2022/08/08 14:18:27 by nelidris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./includes #-fsanitize=address -g

PARS_PATH = srcs/parsing

EXEC_PATH = srcs/executing

READLINE_PATH =  -lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include

GNL = get_next_line/get_next_line.c

PARS_SRCS = $(PARS_PATH)/allocate_memory.c $(PARS_PATH)/error_handling.c \
			$(PARS_PATH)/find_path.c $(PARS_PATH)/here_doc.c \
			$(PARS_PATH)/expand.c $(PARS_PATH)/expand_utils.c \
			$(PARS_PATH)/io_redirections.c $(PARS_PATH)/io_utils.c \
			$(PARS_PATH)/parser.c $(PARS_PATH)/parsing_split.c \
			$(PARS_PATH)/parsing_utils.c $(PARS_PATH)/skip_alloc_utils.c \
			 $(PARS_PATH)/sub_alloc_mem.c $(PARS_PATH)/expand_types.c $(PARS_PATH)/allocate_memory_tool.c \
			 $(PARS_PATH)/error_checker.c $(PARS_PATH)/here_doc_util.c

EXEC_SRCS = $(EXEC_PATH)/builtin_cmds/cd_cmd.c $(EXEC_PATH)/builtin_cmds/echo_cmd.c \
			$(EXEC_PATH)/builtin_cmds/env_cmd.c $(EXEC_PATH)/builtin_cmds/exit_cmd.c \
			$(EXEC_PATH)/builtin_cmds/export_cmd.c $(EXEC_PATH)/builtin_cmds/pwd_cmd.c \
			$(EXEC_PATH)/builtin_cmds/export_cmd_utils1.c $(EXEC_PATH)/builtin_cmds/export_cmd_utils2.c \
			$(EXEC_PATH)/builtin_cmds/unset_cmd.c $(EXEC_PATH)/ptrlen.c \
			$(EXEC_PATH)/env_handler.c $(EXEC_PATH)/free_cmd_line.c $(EXEC_PATH)/builtin_exec.c $(EXEC_PATH)/exec_proc.c \

MAIN_SRCS = main.c

NAME = minishell

LIBFT = libft/libft.a

FT_FPRINTF = ft_fprintf/libftfprintf.a

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

$(NAME) :  $(PARS_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(FT_FPRINTF) $(LIBFT) $(GNL) | header
	@echo $(BLUE)"--------------------------- $(NAME) ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Compiling src files..."$(ENDCOLOR)
	@$(CC) $(CFLAGS) $(READLINE_PATH) $(PARS_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(GNL) $(LIBFT) $(FT_FPRINTF) -o minishell 
	@echo $(GREEN)"---> All files have been compiled successfully!"$(ENDCOLOR)
	
$(FT_FPRINTF): | header
	@echo $(BLUE)"--------------------------- $(FT_FPRINTF) ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Compiling ft_fprintf files..."$(ENDCOLOR)
	@make -C ft_fprintf > /dev/null
	@echo $(GREEN)"---> Ft_fprintf has been compiled successfully!"$(ENDCOLOR)

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
	@echo $(YELLOW)"---> Cleaning ft_fprintf..."$(ENDCOLOR)
	@make fclean -C ft_fprintf/ > /dev/null
	@echo $(GREEN)"---> Ft_fprintf has been cleaned successfully!"$(ENDCOLOR)
	
fclean :  clean | header
	@echo $(BLUE)"--------------------------- fclean ---------------------------"$(ENDCOLOR)
	@echo $(YELLOW)"---> Cleaning minishell..."$(ENDCOLOR)
	@rm -f $(NAME) > /dev/null
	@echo $(GREEN)"---> minishell has been cleaned successfully!"$(ENDCOLOR)

re : fclean all

.PHONY : all clean fclean bonus re