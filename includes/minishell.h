/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:51 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/13 19:13:10 by ahamdy           ###   ########.fr       */
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
# define PERMISSION_DENIED -1
# define NO_SUCH_FILE 1

# define BUFFER_SIZE 1024

typedef struct s_cmd_line
{
	char	*cmd_path;
	char	**command;
	int		in;
	int		out;
	int		is_executable;
}	t_cmd_line;

/* ****************** parcer_functions ****************** */

/* 1 -> function that call all parsing part functions */
t_cmd_line	**parsing_functions(char *prompt_cmd);

/* 2 -> error_handling_functions */
int			error_checker(char *prompt_cmd);
int			exit_code_handler(int mod, int value);
int			check_second_quote(char *sub_prompt_cmd, char quote);
int			skip_white_spaces(char *prompt_cmd, int condition);
int			check_second_quote(char *sub_prompt_cmd, char quote);
void		check_quotes(char *prompt_cmd);
int			check_unexpected_token(char *prompt_cmd, int *index);
int			check_pipe(char *prompt_cmd);
void		check_separators(char *prompt_cmd);
/* 3 -> allocate memory for struct */
int			count_cmd_number(char *prompt_cmd);
t_cmd_line	**initialize_cmd_line(char *prompt_cmd, int cmd_number);
void		free_cmd_args(char **cmd_path);
void		cmd_line_handler(t_cmd_line **cmd,
				char **cmd_after, int cmd_number);
/* sub 3 io_redirection */
void		open_here_doc(char *cmd, int *fd, int last_io_type, int *index);
int			*check_last_io(char *cmd, int mod);
char		*open_file(char *file);
void		redirections_handler(char **cmd_after_split, t_cmd_line **cmd);
int			file_len(char *filename);
void		last_output(t_cmd_line **cmd, int *index, int *fd, int *last);
int			i_redirection(char *cmd, int *index, int *fd, int *in);
void		check_last_fd(char *cmd, int *in, int *out, int *fd);
void		find_io_redirections(char *cmd, int *in, int *out);
int			check_infile(char *cmd, int *in, int *index);
void		is_last_fd(int *fd, int *out, int last_out, int fd_type);
int			open_infile(char *cmd);
int			check_outfile(char *cmd, int *out, int *index);
/* ********* parsing_utils.c ********* */
void		sub_count_arg_number(char *prompt_cmd, int *index);
char		*get_next_line(int fd);
char		*reset_var(int *index);
int			skip_non_arg(char *prompt_cmd, int *index);
int			sub_count_each_arg(char *prompt_cmd, int *index, int *number);
int			skip_io_redirection(char *sub_prompt_cmd);
char		*sub_fill_each_arg(char *cmd_arg, char *prompt_cmd, int *index);
void		here_doc_handler(char **cmd_after_split, t_cmd_line **cmd);
char		*allocate_cmd_path(t_cmd_line *command, char	**envp, char *cmd);
int			env_var_cmp(const char *s1, const char *s2);

/* split with modification */
char		**parsing_split(char const *s, char c);

/*     here_doc    */
int			there_is_quote(char *cmd);
int			limiter_len(char *cmd);
void		store_limiter(char *cmd, char *limiter_name, int len);
char		*get_limiter(char *cmd, int *mod);
int			get_last_heredoc(char *cmd);
void		find_here_docs(char *cmd, int *fd, int last_io_type);
void		check_max_here_doc(char *prompt_cmd);
/* 0-> tmp */
int			count_arg_number(char *prompt_cmd);
int			count_io_redirection(char *prompt_cmd);
int			count_each_arg(char *prompt_cmd, int reset);
char		**allocate_cmd_arguments(char *prompt_cmd);
char		*fill_each_arg(char *cmd_arg, char *prompt_cmd, int reset);
char		*valid_content(char *prompt_cmd, int *index,
				char *var_content, int i);

/*expand*/
void		expand_handler(char **prompt_cmd);
char		*check_valid_content(char *prompt_cmd, int *index,
				char *var_content, int i);
char		*check_is_alpha(char *prompt_cmd, int *index);
char		*check_exit_code(char *prompt_cmd, int *index);
char		*check_is_digit(char *prompt_cmd, int *index);
char		*check_is_quote(char *prompt_cmd, int *index);
int			var_len(char *var);
char		*get_var_name(char *prompt_cmd, int *index);
char		*search_in_env(char *var_name);
char		*check_is_io_alpha(char *prompt_cmd, int *index);
char		*check_env(char *prompt_cmd, int *index, int is_redirection);
char		*check_io_valid_content(char *cmd, int *index,
				char *var_content, int i);
void		check_redirection(char **cmd, int *index,
				char last_char, int *vrai);
int			expand_redirection(char **prompt_cmd, int *index, char last_char);

/* ****************** exec_functions ****************** */

/*  ---------    built-in commands   ---------   */

/* runs built-in commands */
int			run_builtin(t_cmd_line *command);

/* changes directory */
int			cd_command(t_cmd_line *cmd);

/* exports variable to the environment */
int			export_command(t_cmd_line *cmd);
int			export_error(char *var, char *eovn, int *err_occ, char *err_m);
int			is_var_valid(char *var, int *err_occ);
int			var_exist(char *var, int *mod, char **envp);
void		check_export_delimiter(size_t *j, size_t *i, size_t *k, char *var);
void		append_env_var(char *var, char **envp);
void		overwrite_env_var(char *var, char **envp);
void		set_env_var(char *var, int *err_occ, char **envp);
void		add_env_var(char *var, char **envp);
int			ft_strcmp(const char *s1, const char *s2);
void		display_exported_vars(t_cmd_line *cmd, char **envp);

/* unsets variable from the environment */
int			unset_command(t_cmd_line *cmd);

/* echoes arguments to stdout */
int			echo_command(t_cmd_line *cmd);

/* prints all environment variables*/
int			env_command(t_cmd_line *cmd);

/* exits program */
int			exit_command(t_cmd_line *cmd);

/* prints working directory */
int			pwd_command(t_cmd_line *cmd);

/*  ---------    tools   ---------   */

/* returns len of 2d array */
size_t		ptrlen(char	**pstr);

/* executes command line */
int			execute_cmd_line(t_cmd_line **cmd_lines);

/* frees cmd_line */
void		free_cmd_line(t_cmd_line **cmd_line);

/* signals behavior */
void	ctrl_c_handler(int signal);
void	ctrl_c_here_doc_handler(int signal);

/*  ---------    env   ---------   */

/* returns environment pointer or it replaces it with new_envp */
char		**envp_handler(int mod, char **new_envp);

/* duplicates envp into heap */
char		**env_dup(char	**envp);

#endif
