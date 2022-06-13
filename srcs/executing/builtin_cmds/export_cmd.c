/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:28:43 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 15:09:12 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static size_t	env_realloc(char ***envp, size_t n)
{
	char	**tmp_envp;
	size_t	len;

	len = ptrlen(*envp);
	tmp_envp = (char **)malloc(sizeof(char*) * (len + n + 1));
	len = 0;
	while ((*envp)[len])
	{
		tmp_envp[len] = (*envp)[len];
		len++;
	}
	tmp_envp[len] = 0;
	free(*envp);
	*envp = tmp_envp;
	return (len + n);
}

int	export_friendly(char *var)
{
	char	*end_of_name;
	size_t	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	end_of_name = ft_strchr(var, '=');
	if (!end_of_name)
		return (0);
	i = 0;
	while (&var[i] < end_of_name)
	{
		if (!ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int valid_varname(char	*varname)
{
	char	*end_of_var;
	size_t	i;

	if (!ft_isalpha(varname[0]) && varname[0] != '_')
		return (0);
	end_of_var = ft_strchr(varname, '=');
	i = 0;
	while (&varname[i] < end_of_var)
	{
		if (!ft_isalnum(varname[i]) || varname[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

size_t	valid_export_args(char **args)
{
	size_t	i;
	size_t	valid_args;

	i = 1;
	valid_args = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') && valid_varname(args[i]))
			valid_args++;
		i++;
	}
	return (valid_args);
}

void	export_command(t_cmd_line *cmd)
{
	size_t	len;
	size_t	val_args;
	char	**envp;
	
	val_args = valid_export_args(cmd->command);
	envp = envp_handler(GETENV, NULL);
	len = ptrlen(envp);
	env_realloc(&envp, val_args);
	val_args = 1;
	while (cmd->command[val_args])
	{
		if (export_friendly(cmd->command[val_args]))
		{
			envp[len] = cmd->command[val_args];
			len++;
		}
		val_args++;
	}
	envp[len] = 0;
	envp_handler(POSTENV, envp);
}

// int main(int c, char **v, char **envp)
// {
// 	t_cmd_line cmd;
// 	char	*args[] = {"env", 0};
// 	pid_t	pid;

// 	cmd.command = (char **)malloc(sizeof(char*) * 6);
// 	cmd.command[0] = "export";
// 	cmd.command[1] = "HELLO=Y?UPI";
// 	cmd.command[2] = "ROPO=SO*BO";
// 	cmd.command[3] = "POPO=NOPO";
// 	cmd.command[4] = 0;
// 	cmd.command[5] = 0;
// 	envp_handler(POSTENV, env_dup(envp));
// 	export_command(&cmd);
// 	execve("/usr/bin/env", args, envp_handler(GETENV, NULL));
// 	return (0);
// }