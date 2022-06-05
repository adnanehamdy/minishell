/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:12:49 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/03 11:34:15 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input(char *cmd)
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

int	open_output(char *cmd, int mod)
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

void open_io_files(char *cmd, int *in, int *out)
{
	int	index;
	int	*last_in;
	int	*last_out;
	int	fd[2];

	last_in = check_last_io(cmd, 0);
	last_out = check_last_io(cmd, 1);
	index = 0;
	fd[0] = 0;
	fd[1] = 1;
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		if (cmd[index] == '<' && cmd[index] != cmd[index + 1])
		{
			if (fd[0])
			{
				printf("the fd == %d\n has been closed\n", fd[0]);
				close(fd[0]);
			}
			index +=skip_white_spaces(&cmd[index], 0);
			fd[0] = open_input(&cmd[index]);
			if (last_in[1] != INFILE && fd[0] != -1)
			{
				close(fd[0]);
				fd[0] = 0;
			}
			else
				if (fd[0] == -1)
				{
					*in =  PIPE_FAIL;
					printf("it works\n");
					return ;
				}
			else
				printf("fd has been opened  == %d\n", fd[0]);
		}
		else if (cmd[index] == '>')
		{
			if (cmd[index + 1] == '>')
			{
				index++;
				index +=skip_white_spaces(&cmd[index], 0);
				fd[1] = open_output(&cmd[index], 2);
				if (last_out[1] != OUTFILE_APPEND)
				{
					close(fd[1]);
					fd[1] = 0;
				}
				else if (fd[1] == -1)
				{
					*out =  PIPE_FAIL;
					return ;
				}
				else
					printf("fd == %d\n", fd[0]);
			}
			else
			{
				index +=skip_white_spaces(&cmd[index], 0);
				fd[1] = open_output(&cmd[index], 1);
				if (last_out[1] != OUTFILE_WRITE)
				{
					close(fd[1]);
					fd[1] = 0;
				}
				else if (fd[1] == -1)
				{
					*out = PIPE_FAIL;
					return ;
				}
			}
		}
		else if (cmd[index] == '<' && cmd[index + 1] == cmd[index])
			index++;
		index++;
	}
	if (last_in[1] == INFILE)
		*in = fd[0];
	else if (!last_in[0])
		*in = STANDARD_INPUT;
	if ((last_out[1] == OUTFILE_APPEND || last_out[1] == OUTFILE_WRITE) && last_out[0])
		*out = fd[1];
}

void open_io_redirections(char **cmd_after_split, t_cmd_line *cmd)
{
	int	index;
	int	index_y;

	index_y = 0;
	index = 0;
	while (cmd_after_split[index])
	{
		printf("the in before redirections == %d\n", cmd[index].in);
		cmd[index].out = STANDARD_OUTPUT;
		open_io_files(cmd_after_split[index], &cmd[index].in, &cmd[index].out);
		printf("the in fd == %d && the out fd == %d\n", cmd[index].in, cmd[index].out);
		index++;
	}
}