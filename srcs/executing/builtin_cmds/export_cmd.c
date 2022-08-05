/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:21:20 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/05 12:53:16 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int export_error(char *var, char *eovn, int *err_occ, char *err_m)
{
	int	plus_sign;

	if (*err_occ)
		return (0);
	plus_sign = 0;
	if (eovn)
	{
		if (*(eovn - 1) == '+')
			plus_sign++;
		*(eovn - plus_sign) = 0;
	}
	ft_fprintf(STANDARD_ERROR, "export: %s %s\n", err_m, var);
	if (eovn)
	{
		if (*eovn)
			*(eovn - plus_sign) = '+';
		else
			*eovn = '=';
	}
	(*err_occ)++;
	return (0);
}

static int is_var_valid(char *var, int *err_occ)
{
	size_t	i;
	char *eovn;

	eovn = ft_strchr(var, '=');
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (export_error(var, eovn, err_occ, "not an identifier:"));
	if (!eovn)
		return (0);
	i = 1;
	while (&var[i] != eovn)
	{
		if (var[i] == '+' && var[i + 1] == '=')
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (export_error(var, eovn, err_occ, "not a valid identifier:"));
		i++;
	}
	return (1);
}

static int var_exist(char *var, int *mod, char **envp)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (*(ft_strchr(var, '=') - 1) == '+')
		*mod = APPEND;
	i = 0;
	while (envp[i])
	{
		j = 0;
		k = 0;
		while (var[j] != '+' && var[j] != '=')
		{
			if (var[j] != envp[i][k])
				break ;
			j++;
			k++;
		}
		if (var[j] == '+')
			j++;
		if (var[j] == envp[i][k])
			return (1);
		i++;
	}
	return (0);
}

static void	append_env_var(char *var, char **envp)
{
	char	*eovn;
	size_t	i;
	size_t	j;
	size_t	k;
	
	i = 0;
	while (envp[i])
	{
		j = 0;
		k = 0;
		while (var[j] != '+' && var[j] != '=')
		{
			if (var[j] != envp[i][k])
				break ;
			j++;
			k++;
		}
		if (var[j] == '+')
			j++;
		if (var[j] == envp[i][k])
		{
			eovn = envp[i];
			envp[i] = ft_strjoin(envp[i], &var[j + 1]);
			free(eovn);
			return ;
		}
		i++;
	}
}

static void	overwrite_env_var(char *var, char **envp)
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

static void	add_env_var(char *var, char **envp)
{
	char	**new_envp;
	size_t	len;
	size_t	i;

	len = ptrlen(envp);
	new_envp = (char **)malloc(sizeof(char*) * (len + 2));
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

static void	set_env_var(char *var, int *err_occ, char **envp)
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

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void	display_exported_vars(t_cmd_line *cmd, char **envp)
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

int	export_command(t_cmd_line *cmd)
{
	int err_occ;
	int	i;

	if (!cmd->command[1])
		display_exported_vars(cmd, envp_handler(GETENV, NULL));
	err_occ = 0;
	i = 1;
	while (cmd->command[i])
		set_env_var(cmd->command[i++], &err_occ,
			envp_handler(GETENV, NULL));
	return (0);
}