/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:57:06 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/22 10:47:16 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<minishell.h>

int	check_redirection_fail(int *in, int *out, int *fd)
{
	if (fd[0] == -1)
	{
		*in = -1;
		return (1);
	}
	else if (fd[1] == -1)
	{
		*out = -1;
		return (1);
	}
	return (0);
}

void	last_output(t_cmd_line **cmd, int *index, int *fd, int *last)
{
	if (!last[1] && cmd[*index + 1] && (cmd[*index]->out == STANDARD_OUTPUT))
		cmd[*index]->out = fd[1];
	else if (!close(fd[1]) && (cmd[*index]->out == STANDARD_OUTPUT))
	{
		cmd[*index]->out = 1;
		close(fd[1]);
	}
}

int	i_redirection(char *cmd, int *index, int *fd, int *in)
{
	if (cmd[*index] == '"')
	{
		*index = *index + check_second_quote(&cmd[*index], '"', 0);
		(*index)++;
	}
	if (cmd[*index] == '\'')
	{
		*index = *index + check_second_quote(&cmd[*index], '\'', 0);
		(*index)++;
	}
	if (cmd[*index] == '<' && cmd[*index] != cmd[*index + 1])
	{
		if (fd[0])
			close(fd[0]);
		fd[0] = check_infile(cmd, in, index);
		return (0);
	}
	return (1);
}

void	check_last_fd(char *cmd, int *in, int *out, int *fd)
{
	int	*last_in;
	int	*last_out;

	last_in = check_last_io(cmd, 0);
	last_out = check_last_io(cmd, 1);
	if ((last_out[1] == OUTFILE_APPEND
			|| last_out[1] == OUTFILE_WRITE) && last_out[0])
	{
		*out = fd[1];
	}
	else if (fd[1] != 1)
		close(fd[1]);
	if (last_in[1] == INFILE)
		*in = fd[0];
	else if (fd[0])
		close(fd[0]);
	free(last_in);
	free(last_out);
}

void	find_io_redirections(char *cmd, int *in, int *out)
{
	int	index;
	int	fd[2];

	index = 0;
	while (cmd[index])
	{
		if (i_redirection(cmd, &index, fd, in) && cmd[index] == '>')
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = check_outfile(cmd, out, &index);
		}
		else if (cmd[index] == '<' && cmd[index + 1] == cmd[index])
			index++;
		if (cmd[index] && cmd[index] != '"' && cmd[index] != '\'')
			index++;
		if (check_redirection_fail(in, out, fd))
			return ;
	}
	check_last_fd(cmd, in, out, fd);
}
