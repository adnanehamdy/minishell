/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:25:24 by ahamdy            #+#    #+#             */
/*   Updated: 2022/07/03 01:19:39 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_from_stdin(char *buff, int *fd, char *file_name)
{
	while (buff)
	{
		if (!(ft_strncmp(buff, file_name, ft_strlen(file_name)))
			&& (ft_strlen(file_name) == (ft_strlen(buff) - 1)))
			break ;
		write(1, "heredoc>", 8);
		buff = get_next_line(0);
		if (buff && ((ft_strncmp(buff, file_name, ft_strlen(file_name)))
				&& !(ft_strlen(file_name) == (ft_strlen(buff) - 1))))
			write(fd[1], buff, ft_strlen(buff));
	}
}

int	ft_limiter(char *cmd)
{
	char	*buff;
	int		fd[2];
	char	*file_name;

	//fd = (int *)malloc(2 * sizeof(int));
	file_name = open_file(cmd);
	if (pipe(fd) == -1)
	{
		exit_code_handler(POSTEXIT, PIPE_FAIL);
		return (-1);
	}
	write(1, "heredoc>", 8);
	buff = get_next_line(0);
	if (buff && (((ft_strncmp(buff, cmd, ft_strlen(file_name)))
				&& !(ft_strlen(file_name) == (ft_strlen(buff) - 1)))))
		write(fd[1], buff, ft_strlen(buff));
	read_from_stdin(buff, fd, file_name);
	if (buff)
		free(buff);
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
	int stdin_fd;

	here_doc_flag(HERE_DOC_FLAG);
	stdin_fd = dup(0);
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		open_here_doc(cmd, fd, last_io_type, &index);
		if (*fd == PIPE_FAIL)
			break ;
		index++;
	}
	dup2(stdin_fd, 0);
	close(stdin_fd);
	if (here_doc_flag(GET_FLAG) == HERE_DOC_FLAG)
		here_doc_flag(DEFAULT_FLAG);
}

int	get_last_heredoc(char *cmd)
{
	int	index;
	int	fd;
	int	*last_io;

	fd = 0;
	index = 0;
	last_io = check_last_io(cmd, 0);
	if (!last_io[0])
	{
		free(last_io);
		return (STANDARD_INPUT);
	}
	find_here_docs(cmd, &fd, last_io[1]);
	if (last_io[1] != HERE_DOC && fd != PIPE_FAIL)
		fd = STANDARD_INPUT;
	free(last_io);
	return (fd);
}

void	here_doc_handler(char **cmd_after_split, t_cmd_line **cmd)
{
	int	i;

	i = 0;
	while (cmd_after_split[i])
	{
		cmd[i]->in = get_last_heredoc(cmd_after_split[i]);
		i++;
	}
}