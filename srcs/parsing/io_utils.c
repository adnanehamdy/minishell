/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:59:10 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/13 19:04:20 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	file_len(char *filename)
{
	int	index;

	index = 0;
	while (filename[index] && (filename[index] < 9 || filename[index] > 13) &&
		filename[index] != ' ' && filename[index] != '<' && filename[index] != '>')
	{
		if (filename[index] == '"' || filename[index] == '\'')
			index += check_second_quote(&filename[index], filename[index]);
		index++;
	}
	return (index);
}

char	*open_file(char *file)
{
	int	index;
	int	len;
	char *file_name;

	index = 0;
	len = file_len(file);
	file_name = (char *)malloc(sizeof(char) * (len + 1));
	while (index < len && file[index])
	{
		file_name[index] = file[index];
		index++;
	}
	file_name[index] = 0;
	return (file_name);
}

int	*sub_check_last_in(int *last_io, int mod, int deux)
{
	if (deux)
	{
		if (!mod)
			last_io[1] = HERE_DOC;
		else
			last_io[1] = OUTFILE_APPEND;
	}
	else
	{
		if (!mod)
			last_io[1] = INFILE;
		else
			last_io[1] = OUTFILE_WRITE;
	}
	return (last_io);			
}

int	*check_last_io(char *cmd, int mod)
{
	int	index;
	int	*last_io;

	index = -1;
	last_io = (int *)malloc(sizeof(int) * 2);
	last_io[0] = 0;
	last_io[1] = 0;
	if (!cmd)
		return (last_io);
	while (cmd[++index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		if ((cmd[index] == '<' && !mod) || (cmd[index] == '>' && mod))
		{
			if (cmd[index] == cmd[index + 1])
			{	
				index += 1;
				/* last_io[1] =  */ sub_check_last_in(last_io, mod, 1);
			}
			else
				/* last_io[1] = */ sub_check_last_in (last_io, mod, 0);
			last_io[0]++;
		}
	}
	return (last_io);
}

int	check_infile(char *cmd, int *in, int *index)
{
	int	fd;
	int	*last_in;

	last_in = check_last_io(cmd, 0);
	fd = 0;
	*index += skip_white_spaces(&cmd[*index], 0);
	fd = open_infile(&cmd[*index]);
	is_last_fd(&fd, in, last_in[1], INFILE);
	free(last_in);
	return (fd);
}
