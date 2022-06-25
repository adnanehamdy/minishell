/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:28:43 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/24 19:46:27 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	export_env_realloc(char ***envp, char *varname)
{
	char	**tmp_envp;
	size_t	len;

	len = ptrlen(*envp);
	tmp_envp = (char **)malloc(sizeof(char *) * (len + 2));
	len = 0;
	while ((*envp)[len])
	{
		tmp_envp[len] = (*envp)[len];
		len++;
	}
	tmp_envp[len++] = varname;
	tmp_envp[len] = 0;
	free(*envp);
	*envp = tmp_envp;
	return (0);
}

static int	export_friendly(char *var, char **envp)
{
	char	*end_of_name;
	size_t	i;
	size_t	j;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	end_of_name = ft_strchr(var, '=');
	if (!end_of_name)
		return (0);
	j = 0;
	while (envp[j])
	{
		i = 0;
		while (&var[i] < end_of_name)
		{
			if (var[i] != envp[j][i])
				break ;	
			i++;
		}
		if (&var[i] == end_of_name)
		{
			free(envp[j]);
			envp[j] = ft_strdup(var);
			return (0);
		}
		j++;
	}
	i = 0;
	while (&var[i] < end_of_name)
	{
		if (!ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_command(t_cmd_line *cmd)
{
	size_t	i;
	char	**envp;

	envp = envp_handler(GETENV, NULL);
	i = 1;
	while (cmd->command[i])
	{
		if (export_friendly(cmd->command[i], envp))
			export_env_realloc(&envp, cmd->command[i]);
		i++;
	}
	envp_handler(POSTENV, envp);
	return (0);
}
