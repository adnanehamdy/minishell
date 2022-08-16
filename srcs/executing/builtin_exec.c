/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:36:01 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/15 18:51:54 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	run_builtin(t_cmd_line *command, int pipeline)
{
	int	exit_built;

	if (!command->command[0])
		return (0);
	if (!ft_strcmp(command->command[0], "cd"))
		exit_built = cd_command(command);
	else if (!ft_strcmp(command->command[0], "echo"))
		exit_built = echo_command(command);
	else if (!ft_strcmp(command->command[0], "env"))
		exit_built = env_command(command);
	else if (!ft_strcmp(command->command[0], "exit"))
		exit_built = exit_command(command, pipeline);
	else if (!ft_strcmp(command->command[0], "export"))
		exit_built = export_command(command);
	else if (!ft_strcmp(command->command[0], "pwd"))
		exit_built = pwd_command(command);
	else if (!ft_strcmp(command->command[0], "unset"))
		exit_built = unset_command(command);
	else
		return (1);
	if (pipeline)
		exit(exit_built);
	exit_code_handler(POSTEXIT, exit_built);
	return (0);
}
