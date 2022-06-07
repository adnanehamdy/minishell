/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:12:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/06 17:29:01 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	cd_command(t_cmd_line *cmd)
{
	char	*home;

	home = getenv("HOME");
	if (cmd->command[1])
	{
		if (chdir(cmd->command[1]) < 0)
			return ;
	}
	else
	{
		if (chdir(home) < 0)
			return ;
	}
}

// int main(int ac, char **av, char **envp)
// {
// 	t_cmd_line cmd;

// 	cmd.command = (char **)malloc(sizeof(char*) * 3);
// 	cmd.command[0] = "cd";
// 	cmd.command[1] = 0;
// 	cmd.command[2] = 0;
// 	cmd.envp = envp;
// 	cd_command(&cmd);
// 	return (0);
// }