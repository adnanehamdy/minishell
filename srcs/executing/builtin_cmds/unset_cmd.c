/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:25:59 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 14:58:13 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	valid_varname(char *varname)
{
	size_t	i;

	if (!ft_isalpha(varname[0]) && varname[0] != '_')
		return (0);
	if (ft_strchr(varname, '='))
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

static size_t	add_var_or_not(char *arg, char **envp)
{
	size_t	j;

	j = 0;
	while (envp[j])
	{
		if (!ft_strncmp(envp[j], arg, ft_strlen(arg))
			&& envp[j][ft_strlen(arg)] == '=')
			break ;
		j++;
	}
	if (envp[j])
		return (1);
	return (0);
}

size_t	valid_unset_args(char **args, char **envp, int *err_occ)
{
	size_t	i;
	size_t	valid_args;

	i = 1;
	valid_args = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') && valid_varname(args[i]))
			valid_args += add_var_or_not(args[i], envp);
		else
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			if (!(*err_occ))
				(*err_occ)++;
		}
		i++;
	}
	return (valid_args);
}

static int	var_is_in_envp(char	*envp_var, char **args)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] != envp_var[j] || args[i][j] == '=')
				break ;
			j++;
		}
		if (!args[i][j] && (envp_var[j] == '=' || !envp_var[j]))
			return (0);
		i++;
	}
	return (1);
}

int	unset_command(t_cmd_line *cmd)
{
	size_t	len;
	size_t	val_args;
	int		err_occ;
	char	**envp;
	char	**new_envp;

	if (!cmd->command[1])
		return (0);
	envp = envp_handler(GETENV, NULL);
	err_occ = 0;
	val_args = valid_unset_args(cmd->command, envp, &err_occ);
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
	free_cmd_args(envp);
	envp_handler(POSTENV, new_envp);
	return (err_occ);
}
