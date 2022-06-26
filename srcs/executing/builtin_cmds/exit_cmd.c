/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:57:35 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/25 23:04:59 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_command(t_cmd_line *cmd)
{
	size_t	i;

	if (cmd->command[1])
	{
		if (!ft_strncmp("--", cmd->command[1], ft_strlen(cmd->command[1])))
			exit(0);
		if (!ft_isdigit(cmd->command[1][0])
			&& (cmd->command[1][0] != '-' && cmd->command[1][0] != '+'))
		{
			ft_fprintf(STANDARD_ERROR, "minishell: exit: %s: numeric argument required\n",
					cmd->command[1]);
				exit(255);
		}
		i = 1;
		while (cmd->command[1][i])
		{
			if (!ft_isdigit(cmd->command[1][i]))
			{
				ft_fprintf(STANDARD_ERROR, "minishell: exit: %s: numeric argument required\n",
					cmd->command[1]);
				exit(255);
			}
			i++;
		}
		if (ptrlen(cmd->command) > 2)
		{
			ft_fprintf(STANDARD_ERROR, "exit\nminishell: exit: too many arguments\n");
			exit_code_handler(POSTEXIT, 1);
		}
		else
			exit(ft_atoi(cmd->command[1]));
	}
	else
		exit(exit_code_handler(GETEXIT, 0));
	return (0);
}

