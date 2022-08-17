/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:36:01 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 11:30:51 by nelidris         ###   ########.fr       */
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

static void	run_builtin_exit_status(int pipeline,
			int exit_built, int *exit_code)
{
	if (pipeline)
		exit(exit_built);
	if (exit_code)
		*exit_code = exit_built * 256;
	exit_code_handler(POSTEXIT, exit_built);
}

int	run_builtin(t_cmd_line *command, int pipeline, int *exit_code)
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
	run_builtin_exit_status(pipeline, exit_built, exit_code);
	return (0);
}
