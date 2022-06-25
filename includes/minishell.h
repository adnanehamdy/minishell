/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:51 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/25 06:07:22 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_fprintf/ft_fprintf.h"
# include "../libft/libft.h"

# define STANDARD_INPUT 0
# define STANDARD_OUTPUT 1
# define STANDARD_ERROR 2
# define HERE_DOC 3
# define INFILE 4
# define OUTFILE_WRITE 5
# define OUTFILE_APPEND 6
# define INPIPE 7
# define OUTPIPE 8
# define APPEND 9
# define GETEXIT 0
# define POSTEXIT 1
# define GETENV 0
# define POSTENV 1
# define PIPE_FAIL 12

# define BUFFER_SIZE 1024

typedef struct s_cmd_line
{
    char    *cmd_path;
    char    **command;
    int     in;
    int     out;
    int     is_executable;
}    t_cmd_line;

/* ****************** parcer_functions ****************** */

/* 1 -> function that call all parsing part functions */
t_cmd_line	**parsing_functions(char *prompt_cmd);

/* 2 -> error_handling_functions */
void    error_checker(char *prompt_cmd);
int     exit_code_handler(int mod, int value);
int     check_second_quote(char *sub_prompt_cmd, char quote);
int     skip_white_spaces(char *prompt_cmd, int condition);

/* 3 -> allocate memory for struct */
int         count_cmd_number(char *prompt_cmd);
t_cmd_line	**initialize_cmd_line(char *prompt_cmd, int cmd_number);
void        free_cmd_args(char **cmd_path);

/* sub 3 io_redirection */
void	open_here_doc(char *cmd, int *fd, int last_io_type, int *index);
int     *check_last_io(char *cmd, int mod);
char    *open_file(char *file);
void    redirections_handler(char **cmd_after_split, t_cmd_line **cmd);

/* ********* parsing_utils.c ********* */
void	sub_count_arg_number(char *prompt_cmd, int *index);
char	*get_next_line(int fd);
char	*reset_var(int *index);
int     skip_non_arg(char *prompt_cmd, int *index);
int	    sub_count_each_arg(char *prompt_cmd, int *index, int *number);
int	    skip_io_redirection(char *sub_prompt_cmd);
char	*sub_fill_each_arg(char *cmd_arg, char *prompt_cmd, int *index);
void	here_doc_handler(char **cmd_after_split, t_cmd_line **cmd);
char	*allocate_cmd_path(t_cmd_line *command, char	**envp, char *cmd);

/* split with modification */
char	**parsing_split(char const *s, char c);

/* 0-> tmp */
int     count_arg_number(char *prompt_cmd);
int     count_io_redirection(char *prompt_cmd);
int     count_each_arg(char *prompt_cmd,int reset);
char    **allocate_cmd_arguments(char *prompt_cmd);
char    *fill_each_arg(char *cmd_arg, char *prompt_cmd, int reset);

/* ****************** exec_functions ****************** */

/*  ---------    built-in commands   ---------   */

/* runs built-in commands */
int run_builtin(t_cmd_line *command);

/* changes directory */
int cd_command(t_cmd_line *cmd);

/* exports variable to the environment */
int export_command(t_cmd_line *cmd);

/* unsets variable from the environment */
int	unset_command(t_cmd_line *cmd);

/* echoes arguments to stdout */
int echo_command(t_cmd_line *cmd);

/* prints all environment variables*/
int env_command(t_cmd_line *cmd);

/* exits program */
int exit_command(t_cmd_line *cmd);

/* prints working directory */
int pwd_command(t_cmd_line *cmd);

/*  ---------    tools   ---------   */

/* returns len of 2d array */
size_t	ptrlen(char	**pstr);

/* executes command line */
int	execute_cmd_line(t_cmd_line **cmd_lines);

/* frees cmd_line */
void	free_cmd_line(t_cmd_line **cmd_line);

/*  ---------    env   ---------   */

/* returns environment pointer or it replaces it with new_envp */
char	**envp_handler(int mod, char **new_envp);

/* duplicates envp into heap */
char	**env_dup(char	**envp);

#endif
