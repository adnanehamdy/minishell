/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:21:20 by nelidris          #+#    #+#             */
/*   Updated: 2022/07/02 17:25:02 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	valid_var_name(char *var)
{
	size_t	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (!ft_fprintf(STANDARD_ERROR,
			"minishell: export: `%s': not a valid identifier\n", var));
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+' && var[i + 1] == '=')
			break ;
		if (!ft_isalnum(var[i]))
			return (!ft_fprintf(STANDARD_ERROR,
			"minishell: export: `%s': not a valid identifier\n", var));
		i++;	
	}
	return (1);
}

static int		matching_vars(char	*var, char	*envp_var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
	{
		if (var[i] != envp_var[i])
			return (0);
		i++;
	}
	return (1);
}

static char	**find_var(char *var, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (matching_vars(var, envp[i]))
			return (&envp[i]);
		i++;
	}
	return (0);
}

void	replace_var(char *var, char **target_p)
{
	char	*tmp;
	if (*(ft_strchr(var, '=') - 1) == '+')
	{
		tmp = *target_p;
		*target_p = ft_strjoin(*target_p, (ft_strchr(var, '=') + 1));
		free(tmp);
		return ;
	}
	free(*target_p);
	*target_p = ft_strdup(var);
}

void	add_var(char *var, char **envp)
{
	size_t	envp_len;
	size_t	i;
	char	**new_envp;
	
	envp_len = ptrlen(envp);
	new_envp = (char **)malloc(sizeof(char *) * (envp_len + 2));
	i = 0;
	while (envp[i])
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
	char	**target_p;

	if (!valid_var_name(var))
	{
		(*err_occ)++;
		return ;
	}
	if (!ft_strchr(var, '='))
		return ;
	target_p = find_var(var, envp);
	if (target_p)
		replace_var(var, target_p);
	else
		add_var(var, envp);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	sort_envp(t_cmd_line *cmd, char	**envp)
{
	char	**sorted_envp;
	char	*tmp;
	size_t	i;

	sorted_envp = env_dup(envp);
	i = 0;
	while (sorted_envp[i])
	{
		if (sorted_envp[i + 1] && ft_strcmp(sorted_envp[i], sorted_envp[i + 1]) > 0)
		{
			tmp = sorted_envp[i];
			sorted_envp[i] = sorted_envp[i + 1];
			sorted_envp[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (sorted_envp[i])
	{
		ft_fprintf(cmd->out, "declare -x %s\n", sorted_envp[i]);
		free(sorted_envp[i++]);
	}
	free(sorted_envp);
}

int	export_command(t_cmd_line *cmd)
{
	int err_occ;
	int	i;

	err_occ = 0;
	i = 1;
	if (!cmd->command[i])
		sort_envp(cmd, envp_handler(GETENV, NULL));
	while (cmd->command[i])
		set_env_var(cmd->command[i++], &err_occ,
			envp_handler(GETENV, NULL));
		
	return (0);
}