/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:21:20 by nelidris          #+#    #+#             */
/*   Updated: 2022/07/04 17:27:13 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	valid_var_name(char *var)
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

static int	matching_vars(char	*var, char	*envp_var)
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

char	**find_var(char *var, char **envp)
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

int	export_command(t_cmd_line *cmd)
{
	int	err_occ;
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
