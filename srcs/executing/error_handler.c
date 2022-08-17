/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:17:01 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 14:46:48 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_into_fd(char *str, char *command, int fd)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(str, command);
	if (!tmp)
		return ;
	tmp2 = ft_strjoin(tmp, "\n");
	if (!tmp2)
		return ;
	ft_putstr_fd(tmp2, fd);
	free(tmp);
	free(tmp2);
}

void	is_a_directory(t_cmd_line *cmd_line)
{
	DIR	*dir;

	dir = opendir(cmd_line->cmd_path);
	if (cmd_line->cmd_path[0] == '/' && dir)
	{
		closedir(dir);
		print_into_fd("minishell: is a directory: ",
			cmd_line->command[0], STANDARD_ERROR);
		exit(126);
	}
}

void	exec_error_handler(t_cmd_line *cmd_line)
{
	if (cmd_line->is_executable == PERMISSION_DENIED)
	{
		print_into_fd("minishell: permission denied: ",
			cmd_line->command[0], STANDARD_ERROR);
		exit(126);
	}
	else if (cmd_line->cmd_path && ft_strchr(cmd_line->cmd_path, '/'))
	{
		is_a_directory(cmd_line);
		print_into_fd("minishell: no such file or directory: ",
			cmd_line->command[0], STANDARD_ERROR);
	}		
	else
		print_into_fd("minishell: command not found: ",
			cmd_line->command[0], STANDARD_ERROR);
	exit(127);
}
