/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:51 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/13 15:59:20 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<unistd.h>
#include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include<fcntl.h>

#define STANDARD_INPUT 0
#define STANDARD_OUTPUT 1
#define STANDARD_ERROR 2
#define HERE_DOC 3
#define INFILE 4
#define OUTFILE_WRITE 5
#define OUTFILE_APPEND 6
#define INPIPE 7
#define OUTPIPE 8
#define APPEND 9
#define GETEXIT 0
#define POSTEXIT 1
#define GETENV 0
#define POSTENV 1
#define PIPE_FAIL 12

typedef struct s_cmd_line
{
    char    *cmd_path;
    char    **command;
    int     in;
    int     out;
    int     is_executable;
}    t_cmd_line;
#endif

/*******************parcer_functions*******************/

/* 1 -> function that call all parsing part functions */
void    parsing_functions(char *prompt_cmd);

/* 2-> error_handling_functions */
void    error_checker(char *prompt_cmd);
int     exit_code_handler(int mod, int value);
int     check_second_quote(char *sub_prompt_cmd, char quote);
int     skip_white_spaces(char *prompt_cmd, int condition);

/* 3-> allocate memory for struct */
int     count_cmd_number(char *prompt_cmd);
char    **initialize_cmd_line(char *prompt_cmd, int cmd_number);

/*sub 3 io_redirection */
void	open_here_doc(char *cmd, int *fd, int last_io_type, int *index);
int     *check_last_io(char *cmd, int mod);
char    *open_file(char *file);
void    open_io_redirections(char **cmd_after_split, t_cmd_line *cmd);

/********** parsing_utils.c **********/
void	sub_count_arg_number(char *prompt_cmd, int *index);
char	*reset_var(int *index);
int     skip_non_arg(char *prompt_cmd, int *index);
int	    sub_count_each_arg(char *prompt_cmd, int *index, int *number);
int	    skip_io_redirection(char *sub_prompt_cmd);
char	*sub_fill_each_arg(char *cmd_arg, char *prompt_cmd, int *index);
void	here_doc_handler(char **cmd_after_split, t_cmd_line *cmd);

/* split with modification */
char	**parsing_split(char const *s, char c);

/* 0-> tmp */
int     count_arg_number(char *prompt_cmd);
int     count_io_redirection(char *prompt_cmd);
int     count_each_arg(char *prompt_cmd,int reset);
char    **allocate_cmd_arguments(char *prompt_cmd);
char    *fill_each_arg(char *cmd_arg, char *prompt_cmd, int reset);

/*******************exec_functions*******************/

/*  ---------    built-in commands   ---------   */
void	cd_command(t_cmd_line *cmd);
void	export_command(t_cmd_line *cmd);
void	echo_command(t_cmd_line *cmd);
void	env_command(t_cmd_line *command);
void	exit_command( void );
void	pwd_command(void);

/*  ---------    tools   ---------   */
size_t	ptrlen(char	**pstr);

/*  ---------    env   ---------   */
char	**envp_handler(int mod, char **old_envp);
char	**env_dup(char	**envp);
