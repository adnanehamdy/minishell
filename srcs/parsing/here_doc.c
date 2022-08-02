/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:25:24 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/02 15:50:46 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	read_from_stdin(char *buff, int *fd, char *file_name, int mod)
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
		{
			if (mod)
				expand_handler(&buff);
			write(fd[1], buff, ft_strlen(buff));
		}
	}
}
int	there_is_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (cmd[i] < 9 || cmd[i] > 13) &&
		cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int		limiter_len(char *cmd)
{
	int		index;
	char	quote;
	int		quote_number;

	quote_number = 0;
	index = 0;
	while (cmd[index] && (cmd[index] < 9 || cmd[index] > 13) &&
		cmd[index] != ' ' && cmd[index] != '<' && cmd[index] != '>')
	{
		if (cmd[index] == '"' || cmd[index] == '\'')
		{
			quote = cmd[index];
			index++;
			while (cmd[index] != quote)
				index++;
			quote_number += 2;
		}
		index++;
	}
	index -= quote_number;
	return (index);
}

void	store_limiter(char *cmd, char *limiter_name, int len)
{
	int		i;
	int		index;
	char	quote;

	i = 0;
	index = 0;
	while (i < len && cmd[index])
	{
		if (cmd[index] == '"' || cmd[index] == '\'')
		{
			quote = cmd[index];
			index++;
			while (cmd[index] != quote)
			{
				limiter_name[i] = cmd[index];
				i++;
				index++;
			}
			index++;
		}
		limiter_name[i++] = cmd[index++];
	}
	limiter_name[i] = 0;
}

char	*get_limiter(char *cmd, int *mod)
{
	int	index;
	int	len;
	char *limiter_name;
	int	i;

	i = 0;
	index = 0;
	*mod = there_is_quote(cmd);
	len = limiter_len(cmd);
	limiter_name = (char *)malloc(sizeof(char) * (len + 1));
	store_limiter(cmd, limiter_name, len);
	return (limiter_name);
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
	if (buff && (((ft_strncmp(buff, cmd, ft_strlen(file_name)))
				&& !(ft_strlen(file_name) == (ft_strlen(buff) - 1)))))
		{
			if (mod)
				expand_handler(&buff);
			write(fd[1], buff, ft_strlen(buff));
		}
	read_from_stdin(buff, fd, file_name, mod);
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