/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_in_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:59:10 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/25 13:21:00 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_len(char *filename)
{
	int	index;

	index = 0;
	while (filename[index] && filename[index] < 9 && filename > 13 && filename[index] != ' ' && filename[index] != '<' && filename[index] != '>')
	{
		if (filename[index] == '"' || filename[index] == '\'')
			index += check_second_quote(&filename[index], filename[index]);
		index++;
	}
	return (index);
}

open_file(char *file, int here_doc)
{
	int	index;
	int	len;
	char **file_name;

	index = 0;
	len = file_len(file);
	file_name = (char *)malloc(sizeof(char) * (len + 1));
	while (index < len && file[index])
		file_name[index++] = file[index];
	file_name[index] = 0;
	if (here_doc)
}

int	open_in_files(char *cmd)
{
	int	index;
	int	here_doc;
	int	fd;
	int	number;

	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '"')
			index = index + check_second_quote(&cmd[index], '"');
		else if (cmd[index] == '\'')
			index = index + check_second_quote(&cmd[index], '\'');
		if (cmd[index] == '<' && cmd[index + 1] == '<')
		{
			index += 1;
 			index +=skip_white_spaces(&cmd[index], 0);
			fd = open_file(&cmd[index], here_doc);
		}
		index++;
	}
	return (fd);
}