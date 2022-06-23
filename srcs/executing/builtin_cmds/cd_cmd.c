/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:12:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/23 01:07:54 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cd_command(t_cmd_line *cmd)
{
	char	*home;
	

	home = getenv("HOME");
	if (cmd->command[1])
	{
		if (chdir(cmd->command[1]) < 0)
			ft_fprintf(STANDARD_ERROR,
				"minishell: cd: %s: No such file or directory\n", cmd->command[1]);
		return (0);
	}
	else
	{
		if (chdir(home) < 0)
			return (0);
	}
	return (0);
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