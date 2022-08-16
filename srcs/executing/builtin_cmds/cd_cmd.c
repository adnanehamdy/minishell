/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:12:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/15 18:44:09 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_home_env(void)
{
	size_t	i;
	char	**env;

	env = envp_handler(GETENV, 0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("HOME=", env[i], 5))
			return (env[i]);
		i++;
	}
	return (0);
}

int	cd_command(t_cmd_line *cmd)
{
	char	*home;

	home = get_home_env();
	if (cmd->command[1])
	{
		if (chdir(cmd->command[1]) < 0)
		{
			ft_fprintf(STANDARD_ERROR,
				"minishell: cd: %s: No such file or directory\n",
				cmd->command[1]);
			return (1);
		}
	}
	else
	{
		if (chdir(&home[5]) < 0)
		{
			ft_fprintf(STANDARD_ERROR, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	return (0);
}
