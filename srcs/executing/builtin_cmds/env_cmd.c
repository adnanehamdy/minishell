/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 16:01:00 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env_command(t_cmd_line *command)
{
	int	i;
	char	**envp;

	(void)command;
	envp = envp_handler(GETENV, NULL);
	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], STANDARD_OUTPUT);
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