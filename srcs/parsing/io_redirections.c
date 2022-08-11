/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:41:11 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/08 21:34:12 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_infile(char *cmd)
{
	char	*filename;
	int		fd;

	filename = open_file(cmd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (!access(filename, F_OK))
			ft_fprintf(STANDARD_ERROR, "minishell : permission denied : %s\n", filename);
		else
			ft_fprintf(STANDARD_ERROR, "minishell : no such file or directory : %s\n", filename);
	}
	free(filename);
	return (fd);
}

int	open_outfile(char *cmd, int mod)
{
	char	*filename;
	int		fd;

	filename = open_file(cmd);
	if (mod == 1)
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		if (!access(filename, F_OK))
			ft_fprintf(STANDARD_ERROR, "minishell : permission denied : %s\n", filename);
		else
			ft_fprintf(STANDARD_ERROR, "minishell : no such file or directory : %s\n", filename);
	}
	free(filename);
	return (fd);
}

void	is_last_fd(int *fd, int *out, int last_out, int fd_type)
{
	if (*fd == -1)
	{
		*out =  PIPE_FAIL;
		*fd = -1;
		return ;
	}
	else if (last_out != fd_type)
	{
		close(*fd);
		*fd = 0;
	}
}

int	check_infile(char *cmd, int *in, int *index,  int last_in)
{
	int	fd;

	fd = 0;

	*index += skip_white_spaces(&cmd[*index], 0);
	fd = open_infile(&cmd[*index]);
	is_last_fd(&fd, in, last_in, INFILE);
	return (fd);
}

int check_outfile(char *cmd, int *out, int *index, int last_out)
{
	int	fd;

	fd = 0;
	if (cmd[*index + 1] == '>')
	{
		*index = *index + 1;
		*index += skip_white_spaces(&cmd[*index], 0);
		fd = open_outfile(&cmd[*index], 2);
		is_last_fd(&fd, out, last_out, OUTFILE_APPEND);
	}
	else
	{
		*index += skip_white_spaces(&cmd[*index], 0);
		fd = open_outfile(&cmd[*index], 1);
		is_last_fd(&fd, out, last_out, OUTFILE_WRITE);
	}
	return (fd);
}

void find_io_redirections(char *cmd, int *in, int *out)
{
	int	index;
	int	fd[2];
	int	*last_in;
	int	*last_out;

	index = 0;
	last_in = check_last_io(cmd, 0);
	last_out = check_last_io(cmd, 1);
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		if (cmd[index] == '<' && cmd[index] != cmd[index + 1])
		{
			if (fd[0])
				close(fd[0]);
			fd[0] = check_infile(cmd, in, &index, last_in[1]);
		}
		else if (cmd[index] == '>')
		{
			if (fd[1])
				close(fd[1]);
			fd[1] = check_outfile(cmd, out, &index, last_out[1]);
		}
		else if (cmd[index] == '<' && cmd[index + 1] == cmd[index])
			index++;
		index++;
		if (fd[0] == -1)
		{
			*in = -1;
			free(last_in);
			free(last_out);
			return ;
		}
		else if (fd[1] == -1)
		{
			*out = -1;
			free(last_out);
			free(last_out);
			return ;
		}
	}
	if ((last_out[1] == OUTFILE_APPEND || last_out[1] == OUTFILE_WRITE) && last_out[0])
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

void redirections_handler(char **cmd_after_split, t_cmd_line **cmd)
{
	int	index;
	int	fd[2];
	int	*last_in = NULL;
	int	*last_out = NULL;
	index = 0;
	while (cmd_after_split[index])
	{
		last_in = check_last_io(cmd_after_split[index + 1], 0);
		last_out = check_last_io(cmd_after_split[index], 1);
		pipe(fd);
		if (cmd[index + 1])
			cmd[index + 1]->in = STANDARD_INPUT;
		cmd[index]->out = STANDARD_OUTPUT;
		find_io_redirections(cmd_after_split[index], &cmd[index]->in, &cmd[index]->out);
		if (!last_in[0] && cmd_after_split[index + 1])
			cmd[index + 1]->in = fd[0];
		else
			close(fd[0]);
		if (!last_out[1] &&  cmd[index + 1] && (cmd[index]->out == STANDARD_OUTPUT))
			cmd[index]->out = fd[1];
		else if (!close(fd[1]) && (cmd[index]->out == STANDARD_OUTPUT))
		{
			cmd[index]->out = 1;
			close(fd[1]);
		}
		index++;
		free(last_in);
		free(last_out);
	}
}
