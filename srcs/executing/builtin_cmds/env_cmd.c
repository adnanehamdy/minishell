/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/23 23:34:11 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_command(t_cmd_line *cmd)
{
	int		i;
	char	**envp;

	(void)cmd;
	envp = envp_handler(GETENV, NULL);
	i = 0;
	while (envp[i])
		ft_fprintf(cmd->out, "%s\n", envp[i++]);
	return (0);
}
