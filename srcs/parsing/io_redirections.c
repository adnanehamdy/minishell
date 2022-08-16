/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:41:11 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/16 17:56:54 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_infile(char *cmd)
{
	char	*filename;
	int		fd;
	int		true;

	true = 0;
	if (cmd[0] == '$')
		true = 1;
	filename = open_file(cmd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (!access(filename, F_OK))
			ft_fprintf(STANDARD_ERROR,
				"minishell : permission denied : %s\n", filename);
		else if (true == 1)
			ft_fprintf(STANDARD_ERROR,
				"minishell : ambiguous redirect : %s\n", filename);
		else
			ft_fprintf(STANDARD_ERROR,
				"minishell : no such file or directory : %s\n", filename);
	}
	free(filename);
	return (fd);
}

int	open_outfile(char *cmd, int mod)
{
	char	*filename;
	int		fd;
	int		true;

	true = 0;
	if (cmd[0] == '$')
		true = 1;
	filename = open_file(cmd);
	if (mod == 1)
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		if (!access(filename, F_OK))
			ft_fprintf(STANDARD_ERROR,
				"minishell : permission denied : %s\n", filename);
		else if (true == 1)
			ft_fprintf(STANDARD_ERROR,
				"minishell : ambiguous redirect : %s\n", filename);
		else
			ft_fprintf(STANDARD_ERROR,
				"minishell : no such file or directory : %s\n", filename);
	}
	free(filename);
	return (fd);
}

void	is_last_fd(int *fd, int *out, int last_out, int fd_type)
{
	if (*fd == -1)
	{
		*out = PIPE_FAIL;
		*fd = -1;
		return ;
	}
	else if (last_out != fd_type)
	{
		close(*fd);
		*fd = 0;
	}
}

int	check_outfile(char *cmd, int *out, int *index)
{
	int	fd;
	int	*last_out;

	last_out = check_last_io(cmd, 1);
	fd = 0;
	if (cmd[*index + 1] == '>')
	{
		*index = *index + 1;
		*index += skip_white_spaces(&cmd[*index], 0);
		fd = open_outfile(&cmd[*index], 2);
		is_last_fd(&fd, out, last_out[1], OUTFILE_APPEND);
	}
	else
	{
		*index += skip_white_spaces(&cmd[*index], 0);
		fd = open_outfile(&cmd[*index], 1);
		is_last_fd(&fd, out, last_out[1], OUTFILE_WRITE);
	}
	free(last_out);
	return (fd);
}

void	redirections_handler(char **cmd_after_split, t_cmd_line **cmd)
{
	int	index;
	int	fd[2];
	int	*last_in;
	int	*last_out;

	index = 0;
	while (cmd_after_split[index])
	{
		last_in = check_last_io(cmd_after_split[index + 1], 0);
		last_out = check_last_io(cmd_after_split[index], 1);
		pipe(fd);
/* 		if (cmd[index + 1] && cmd[index + 1])
			cmd[index + 1]->in = STANDARD_INPUT; */
		cmd[index]->out = STANDARD_OUTPUT;
		find_io_redirections(cmd_after_split[index],
			&cmd[index]->in, &cmd[index]->out);
		if (!last_in[0] && cmd_after_split[index + 1])
			cmd[index + 1]->in = fd[0];
		else
			close(fd[0]);
		last_output(cmd, &index, fd, last_out);
		index++;
		free(last_in);
		free(last_out);
	}
}
