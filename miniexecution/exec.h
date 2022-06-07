/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:56:32 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/07 09:23:14 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EXEC_H__
# define __EXEC_H__

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>

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

typedef struct s_cmd_line
{
    char    *cmd_path;
    char    **command;
    char    **envp;
    int     in;
    int     out;
    int     is_executable;
}    t_cmd_line;

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


#endif /* __EXEC_H__ */