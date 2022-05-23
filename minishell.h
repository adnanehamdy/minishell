/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:51 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/23 11:18:19 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<unistd.h>
#include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define STANDARD_INPUT 0
#define STANDARD_OUTPUT 1
#define STANDARD_ERROR 2
#define HERE_DOC 3
#define INFILE 4
#define OUTFILE_WRITE 5
#define OUTFILE_APPEND 6
#define INPIPE 7
#define OUTPIPE 8
#define GETEXIT 0
#define POSTEXIT 1

typedef struct s_io_redir
{
    char    **io_path;
    size_t    io_len;
    int      *type_input;
    
}    t_io_redir;

typedef struct s_cmd_line
{
    char    **command;
    char    **envp;
    t_io_redir    *io_redir;
}    t_cmd_line;
#endif

/*******************parcer_functions*******************/

/* 1 -> function that call all parsing part functions */
void	parsing_functions(char *prompt_cmd);

/* 2-> error_handling_functions */
void	error_checker(char *prompt_cmd);
int	exit_code_handler(int mod, int value);
int	check_second_quote(char *sub_prompt_cmd, char quote);
int	skip_white_spaces(char *prompt_cmd, int condition);

/* 3-> allocate memory for struct */
int	count_cmd_number(char *prompt_cmd);
/* t_cmd_line *initialize_cmd_line(char *prompt_cmd, int cmd_number);*/
char   **initialize_cmd_line(char *prompt_cmd, int cmd_number);
char	*ft_substr(char const *s, unsigned int start, size_t len);



/* 0-> tmp */
int	count_arg_number(char *prompt_cmd);
int	count_io_redirection(char *prompt_cmd);
int	count_each_arg(char *prompt_cmd,int reset);
 char **allocate_cmd_arguments(char *prompt_cmd, int cmd_number, t_cmd_line *cmd);
 char *fill_each_arg(char *cmd_arg, char *prompt_cmd, int reset);
 char	**ft_split(char const *s, char c);