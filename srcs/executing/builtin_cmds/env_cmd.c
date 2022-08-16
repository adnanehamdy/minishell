/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/15 14:49:48 by ahamdy           ###   ########.fr       */
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
	{
		if (ft_strchr(envp[i], '='))
			ft_fprintf(cmd->out, "%s\n", envp[i]);
		i++;
	}
	return (0);
}
