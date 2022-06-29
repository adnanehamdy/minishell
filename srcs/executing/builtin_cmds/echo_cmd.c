/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:23:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/23 23:34:13 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo_command(t_cmd_line *cmd)
{
	int	new_line;
	int	i;
	int	j;

	new_line = 0;
	i = 1;
	while (cmd->command[i] && cmd->command[i][0] == '-')
	{
		j = 1;
		while (cmd->command[i][j] && cmd->command[i][j] == 'n')
			j++;
		if (cmd->command[i][j])
			break ;
		new_line++;
		i++;
	}
	i = new_line + 1;
	while (cmd->command[i])
	{
		ft_fprintf(cmd->out, "%s", cmd->command[i++]);
		if (cmd->command[i])
			ft_fprintf(cmd->out, " ");
	}
	if (!new_line)
		ft_fprintf(cmd->out, "\n");
	return (0);
}
