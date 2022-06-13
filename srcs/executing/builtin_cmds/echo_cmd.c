/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:23:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 14:54:30 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	echo_command(t_cmd_line *cmd)
{
	int	new_line;
	int i;
	int	j;

	new_line = 0;
	i = 1;
	while (cmd->command[i] && cmd->command[i][0] == '-')
	{
		j = 1;
		while (cmd->command[i][j] && cmd->command[i][j] == 'n')
			j++;
		if (cmd->command[i][j])
			break;
		new_line++;
		i++;
	}
	i = new_line + 1;
	while (cmd->command[i])
	{
		ft_putstr_fd(cmd->command[i++], STANDARD_OUTPUT);
		if (cmd->command[i])
			ft_putstr_fd(" ", STANDARD_OUTPUT);
	}
	if (!new_line)
		ft_putstr_fd("\n", STANDARD_OUTPUT);
}

// int main(void)
// {
// 	t_cmd_line cmd;

// 	cmd.command = (char **)malloc(sizeof(char*) * 6);
// 	cmd.command[0] = "echo";
// 	cmd.command[1] = "-nnnnnnnnnnnj";
// 	cmd.command[2] = "-n";
// 	cmd.command[3] = "-n";
// 	cmd.command[4] = "okey";
// 	cmd.command[5] = 0;
// 	echo_command(&cmd);
// 	return (0);
// }