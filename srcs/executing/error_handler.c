/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:17:01 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 10:11:09 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_error_handler(t_cmd_line *cmd_line)
{
	if (cmd_line->is_executable == PERMISSION_DENIED)
	{
		ft_putstr_fd("minishell: permission denied: ", STANDARD_ERROR);
		ft_putendl_fd(cmd_line->command[0], STANDARD_ERROR);
		exit(126);
	}
	else if (cmd_line->cmd_path && ft_strchr(cmd_line->cmd_path, '/'))
	{
		ft_putstr_fd("minishell: no such file or directory: ", STANDARD_ERROR);
		ft_putendl_fd(cmd_line->command[0], STANDARD_ERROR);
	}		
	else
	{
		ft_putstr_fd("minishell: command not found: ", STANDARD_ERROR);
		ft_putendl_fd(cmd_line->command[0], STANDARD_ERROR);
	}
	exit(127);
}
