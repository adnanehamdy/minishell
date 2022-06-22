/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:36:01 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/21 23:57:52 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_builtin(t_cmd_line *command)
{
	if (!command->command[0])
		return (0);
	if (!ft_strncmp(command->command[0], "cd",
			ft_strlen(command->command[0])))
		return (cd_command(command));
	else if (!ft_strncmp(command->command[0], "echo",
			ft_strlen(command->command[0])))
		return (echo_command(command));
	else if (!ft_strncmp(command->command[0], "env",
			ft_strlen(command->command[0])))
		return (env_command(command));
	else if (!ft_strncmp(command->command[0], "exit",
			ft_strlen(command->command[0])))
		return (exit_command(command));
	else if (!ft_strncmp(command->command[0], "export",
			ft_strlen(command->command[0])))
		return (export_command(command));
	else if (!ft_strncmp(command->command[0], "pwd",
			ft_strlen(command->command[0])))
		return (pwd_command(command));
	else if (!ft_strncmp(command->command[0], "unset",
			ft_strlen(command->command[0])))
		return (unset_command(command));
	return (1);
}
