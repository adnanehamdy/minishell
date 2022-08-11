/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:25:24 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/09 18:34:55 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_from_stdin(char *buff, int *fd, char *file_name, int mod)
{
	if (buff && !(ft_strncmp(buff, file_name, ft_strlen(file_name)))
		&& (ft_strlen(file_name) == (ft_strlen(buff) - 1)))
	{
		free(buff);
		return ;
	}
	while (buff)
	{
		free(buff);
		buff = 0;
		write(1, "heredoc>", 8);
		buff = get_next_line(0);
		if (!(ft_strncmp(buff, file_name, ft_strlen(file_name)))
			&& (ft_strlen(file_name) == (ft_strlen(buff) - 1)))
			break ;
		if (buff)
		{
			if (mod)
				expand_handler(&buff);
			write(fd[1], buff, ft_strlen(buff));
		}
	}
	if (buff)
		free(buff);
}

int	ft_limiter(char *cmd)
{
	char	*buff;
	int		fd[2];
	char	*file_name;
	int		mod;

	file_name = get_limiter(cmd, &mod);
	if (pipe(fd) == -1)
	{
		exit_code_handler(POSTEXIT, PIPE_FAIL);
		return (-1);
	}
	write(1, "heredoc>", 8);
	buff = get_next_line(0);
	if (buff && ((ft_strncmp(buff, file_name, ft_strlen(file_name)))))
	{
		if (mod)
			expand_handler(&buff);
		write(fd[1], buff, ft_strlen(buff));
	}
	read_from_stdin(buff, fd, file_name, mod);
	free(file_name);
	close(fd[1]);
	return (fd[0]);
}

void	open_here_doc(char *cmd, int *fd, int last_io_type, int *index)
{
	if (cmd[*index] == '<' && cmd[*index + 1] == '<')
	{
		if (*fd)
			close(*fd);
		*index += 1;
		*index += skip_white_spaces(&cmd[*index], 0);
		*fd = ft_limiter(&cmd[*index]);
		if (*fd == -1)
		{
			*fd = PIPE_FAIL;
			return ;
		}
		if (last_io_type != HERE_DOC)
		{
			close(*fd);
			*fd = 0;
		}
	}
}

void	find_here_docs(char *cmd, int *fd, int last_io_type)
{
	int	index;

	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '"')
		{
			index = index + check_second_quote(&cmd[index], '"');
			index++;
		}
		else if (cmd[index] == '\'')
		{
			index = index + check_second_quote(&cmd[index], '\'');
			index++;
		}
		open_here_doc(cmd, fd, last_io_type, &index);
		if (*fd == PIPE_FAIL)
			break ;
		if (cmd[index] != '"' && cmd[index] != '\'')
			index++;
	}
}

void ctrl_c_here_doc_handler(int signal)
{
	(void)signal;
	close(0);
	write(1, "\n", 1);
}

void	here_doc_handler(char **cmd_after_split, t_cmd_line **cmd)
{
	int	i;
	int fd_in;

	i = 0;
	fd_in = dup(0);
	signal(SIGINT, ctrl_c_here_doc_handler);
	while (cmd_after_split[i])
	{
		cmd[i]->in = get_last_heredoc(cmd_after_split[i]);
		i++;
	}
	signal(SIGINT, ctrl_c_handler);
	dup2(fd_in, 0);
	close(fd_in);
}
