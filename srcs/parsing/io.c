
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:12:49 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/17 11:57:12 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(char *cmd)
{
	char	*filename;
	int		fd;

	filename = open_file(cmd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (!access(filename, F_OK))
			printf("minishell : permission denied : %s\n", filename);
		else
			printf("minishell : no such file or directory : %s\n", filename);
	}
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
			printf("minishell : permission denied : %s\n", filename);
		else
			printf("minishell : no such file or directory : %s\n", filename);
	}
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
	*index +=skip_white_spaces(&cmd[*index], 0);
	printf(" first %c\n ", cmd[*index]);
	fd = open_infile(&cmd[*index]);
	printf("after %c\n ", cmd[*index]);
	is_last_fd(&fd, in, last_in, INFILE);
	return (fd);
}

int	infiles_handler(char *cmd, int *in)
{
	int	index;
	int	*last_in;
	int	fd;

	fd = 0;
	index = 0;
	last_in = check_last_io(cmd, 0);
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		if (cmd[index] == '<' && cmd[index] != cmd[index + 1])
			fd = check_infile(cmd, in, &index, last_in[1]);
		else if (cmd[index] == '<' && cmd[index + 1] == cmd[index])
			index++;
		index++;
	}
	if (last_in[1] == INFILE)
		*in = fd;
	// else if (!last_in[0])
	// 	*in = STANDARD_INPUT;
	return (fd);
}


int check_outfile(char *cmd, int *out, int *index, int last_out)
{
	int	fd;

	fd = 0;
	if (cmd[*index + 1] == '>')
	{
		*index = *index + 1;
		*index +=skip_white_spaces(&cmd[*index], 0);
		fd = open_outfile(&cmd[*index], 2);
		is_last_fd(&fd, out, last_out, OUTFILE_APPEND);
	}
	else
	{
		*index +=skip_white_spaces(&cmd[*index], 0);
		fd = open_outfile(&cmd[*index], 1);
		is_last_fd(&fd, out, last_out, OUTFILE_WRITE);
	}
	return (fd);
}

void	outfiles_handler(char *cmd, int *out)
{
	int	index;
	int	*last_out;
	int	fd;

	fd = 1;
	index = 0;
	last_out = check_last_io(cmd, 1);
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		else if (cmd[index] == '>')
			fd = check_outfile(cmd, out, &index, last_out[1]);
		if (fd == -1)
			return ;
		index++;
	}
	if ((last_out[1] == OUTFILE_APPEND || last_out[1] == OUTFILE_WRITE) && last_out[0])
		*out = fd;
}


void redirections_handler(char **cmd_after_split, t_cmd_line **cmd)
{
	int	index;
	int	*last_in;
	int	*last_out;
	int	fd[2];

	index = 0;
	while (cmd_after_split[index])
	{
		// check_redirections(cmd_after_split[index], cmd)
		pipe(fd);
		last_in = check_last_io(cmd_after_split[index], 0);
		last_out = check_last_io(cmd_after_split[index], 1);
		if (last_in[0] && !close(fd[0]))
			infiles_handler(cmd_after_split[index], &cmd[index]->in);
		else if (!last_in[0] && index)
			cmd[index]->in = fd[0];
		else
			cmd[index]->in = close(fd[0]);
		if (last_out[1] && !close(fd[1]))
			outfiles_handler(cmd_after_split[index], &cmd[index]->out);
		else if (!last_out[1] && cmd[index + 1])
			cmd[index]->out = fd[1];
		else if (close(fd[1]))
			cmd[index]->out = 1;
		printf("the in fd == %d && the out fd == %d\n", cmd[index]->in, cmd[index]->out);
		index++;
	}
}