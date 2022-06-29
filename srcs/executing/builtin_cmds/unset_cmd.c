/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:25:59 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/23 23:33:57 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unset_friendly(char *var)
{
	char	*end_of_name;
	size_t	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	end_of_name = ft_strchr(var, '=');
	if (end_of_name)
		return (0);
	i = 0;
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_varname(char *varname)
{
	char	*end_of_var;
	size_t	i;

	if (!ft_isalpha(varname[0]) && varname[0] != '_')
		return (0);
	end_of_var = ft_strchr(varname, '=');
	if (end_of_var)
		return (0);
	i = 0;
	while (varname[i])
	{
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

size_t	valid_unset_args(char **args)
{
	size_t	i;
	size_t	valid_args;
	int		err_occ;

	i = 1;
	valid_args = 0;
	err_occ = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') && valid_varname(args[i]))
			valid_args++;
		else if (!err_occ)
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			err_occ++;
		}
		i++;
	}
	return (valid_args);
}

static int var_is_in_envp(char	*envp_var, char **args)
{
	size_t	i;
	size_t	j;
	char	*end_of_name;

	end_of_name = ft_strchr(envp_var, '=');
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] != envp_var[j] || args[i][j] == '=')
				break;
			j++;
		}
		if (!args[i][j])
			return (0);
		i++;
	}
	return (1);
}

int	unset_command(t_cmd_line *cmd)
{
	size_t	len;
	size_t	val_args;
	char	**envp;
	char	**new_envp;

	if (!cmd->command[1])
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (0);
	}
	val_args = valid_unset_args(cmd->command);
	envp = envp_handler(GETENV, NULL);
	len = ptrlen(envp);
	new_envp = (char **)malloc(sizeof(char *) * (len - val_args + 1));
	len = 0;
	val_args = 0;
	while (envp[len])
	{
		if (var_is_in_envp(envp[len], cmd->command))
			new_envp[val_args++] = ft_strdup(envp[len]);
		len++;	
	}
	new_envp[val_args] = 0;
	envp_handler(POSTENV, new_envp);
	return (0);
}