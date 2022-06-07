/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/06 17:29:05 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	env_command(t_cmd_line *command)
{
	int	i;

	i = 0;
	while (command->envp[i])
		ft_putendl_fd(command->envp[i++], STANDARD_OUTPUT);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_cmd_line cmd;

// 	cmd.command = (char **)malloc(sizeof(char*) * 2);
// 	cmd.command[0] = "env";
// 	cmd.command[1] = 0;
// 	cmd.envp = envp;
// 	env_command(&cmd);
// 	return (0);
// }