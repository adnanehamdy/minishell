/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:36:01 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/30 10:16:39 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	int ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	run_builtin(t_cmd_line *command)
{
	if (!command->command[0])
		return (0);
	if (!ft_strcmp(command->command[0], "cd"))
		return (cd_command(command));
	else if (!ft_strcmp(command->command[0], "echo"))
		return (echo_command(command));
	else if (!ft_strcmp(command->command[0], "env"))
		return (env_command(command));
	else if (!ft_strcmp(command->command[0], "exit"))
		return (exit_command(command));
	else if (!ft_strcmp(command->command[0], "export"))
		return (export_command(command));
	else if (!ft_strcmp(command->command[0], "pwd"))
		return (pwd_command(command));
	else if (!ft_strcmp(command->command[0], "unset"))
		return (unset_command(command));
	return (1);
}
