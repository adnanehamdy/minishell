/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:42:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/05 17:59:53 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	overwrite_env_var(char *var, char **envp)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (var[j] != '+' && var[j] != '=')
		{
			if (var[j] != envp[i][j])
				break ;
			j++;
		}
		if (var[j] == '+')
			j++;
		if (var[j] == envp[i][j])
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
}

void	add_env_var(char *var, char **envp)
{
	char	**new_envp;
	size_t	len;
	size_t	i;

	len = ptrlen(envp);
	new_envp = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i < len)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i++] = ft_strdup(var);
	new_envp[i] = 0;
	free(envp);
	envp_handler(POSTENV, new_envp);
}

void	set_env_var(char *var, int *err_occ, char **envp)
{
	int	mod;

	mod = 0;
	if (!is_var_valid(var, err_occ))
		return ;
	if (var_exist(var, &mod, envp))
	{
		if (mod == APPEND)
			append_env_var(var, envp);
		else
			overwrite_env_var(var, envp);
		return ;
	}
	add_env_var(var, envp);
}

void	display_exported_vars(t_cmd_line *cmd, char **envp)
{
	size_t	j;
	size_t	len;
	char	*p;
	char	**new_envp;

	new_envp = env_dup(envp);
	len = ptrlen(envp);
	j = 0;
	while (j < len)
	{
		if (j < len - 1 && ft_strcmp(new_envp[j], new_envp[j + 1]) > 0)
		{
			p = new_envp[j];
			new_envp[j] = new_envp[j + 1];
			new_envp[j + 1] = p;
			j = 0;
		}
		j++;
	}
	j = 0;
	while (envp[j])
		ft_fprintf(cmd->out, "declare -x %s\n", new_envp[j++]);
	free_cmd_args(new_envp);
}
