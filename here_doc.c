/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:25:24 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/31 12:01:49 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_from_stdin(char *buff, int *fd, char *file_name)
{
	while (buff)
	{
		if (!(ft_strncmp(buff, file_name, ft_strlen(file_name)))
			&& (ft_strlen(file_name) == (ft_strlen(buff) - 1)))
			break ;
		write(1, "heredoc>", 8);
		buff = get_next_line(0);
		if (((ft_strncmp(buff, file_name, ft_strlen(file_name)))
				&& !(ft_strlen(file_name) == (ft_strlen(buff) - 1))))
			write(fd[1], buff, ft_strlen(buff));
	}
}

int	ft_limiter(char *cmd)
{
	char	*buff;
	int		*fd;
	char	*file_name;

	fd = (int *)malloc(2 * sizeof(int));
	file_name = open_file(cmd);
	if (pipe(fd) == -1)
	{
		exit_code_handler(POSTEXIT, PIPE_FAIL);
		return (-1);
	}
	write(1, "heredoc>", 8);
	buff = get_next_line(0);
	if ((((ft_strncmp(buff, cmd, ft_strlen(file_name)))
				&& !(ft_strlen(file_name) == (ft_strlen(buff) - 1)))))
		write(fd[1], buff, ft_strlen(buff));
	read_from_stdin(buff, fd, file_name);
	free(buff);
	free(file_name);
	close(fd[0]);
	return (fd[1]);
}

int	open_here_doc(char *cmd)
{
	int	index;
	int	fd;
	int	*last_io;

	fd = 0;
	index = 0;
	last_io = check_last_io(cmd, 0);
	if (!last_io[0])
	{
		fd = STANDARD_INPUT;
		return (fd);
	}
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		if (cmd[index] == '<' && cmd[index + 1] == '<')
		{
			if (fd)
				close(fd);
			index += 1;
 			index +=skip_white_spaces(&cmd[index], 0);
			fd = ft_limiter(&cmd[index]);
			if (fd == -1)
				return (PIPE_FAIL);
			if (last_io[1] != HERE_DOC)
			{
				close(fd);
				fd = 0;
			}
		}
		index++;
	}
	if (last_io[1] != HERE_DOC)
		fd = STANDARD_INPUT;
	return (fd);
}