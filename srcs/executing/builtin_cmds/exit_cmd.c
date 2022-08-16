/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:57:35 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/16 11:01:06 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_status_check(t_cmd_line *cmd)
{
	size_t	i;

	if (!ft_strcmp("--", cmd->command[1]))
		exit(exit_code_handler(GETEXIT, 0));
	if (!ft_isdigit(cmd->command[1][0])
		&& (cmd->command[1][0] != '-' && cmd->command[1][0] != '+'))
	{
		ft_fprintf(STANDARD_ERROR,
			"exit\nminishell: exit: %s: numeric argument required\n",
			cmd->command[1]);
		exit(255);
	}
	i = 1;
	while (cmd->command[1][i])
	{
		if (!ft_isdigit(cmd->command[1][i]) || !ft_strcmp(cmd->command[1], "-"))
		{
			ft_fprintf(STANDARD_ERROR,
				"exit\nminishell: exit: %s: numeric argument required\n",
				cmd->command[1]);
			exit(255);
		}
		i++;
	}
}

int	exit_command(t_cmd_line *cmd, int pipeline)
{
	if (cmd->command[1])
	{
		exit_status_check(cmd);
		if (ptrlen(cmd->command) > 2)
		{
			ft_fprintf(STANDARD_ERROR,
				"minishell: exit: too many arguments\n");
		}
		else
		{
			exit(ft_atoi(cmd->command[1]));
			if (!pipeline)
				ft_fprintf(STANDARD_ERROR, "exit\n");
		}
	}
	else
	{
		if (!pipeline)
			ft_fprintf(STANDARD_ERROR, "exit\n");
		exit(exit_code_handler(GETEXIT, 0));
	}
	exit_code_handler(POSTEXIT, 1);
	return (0);
}
