/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:42:58 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/15 17:55:17 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export_error(char *var, char *eovn, int *err_occ, char *err_m)
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

int	is_var_valid(char *var, int *err_occ)
{
	size_t	i;
	char	*eovn;

	eovn = ft_strchr(var, '=');
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (export_error(var, eovn, err_occ, "not an identifier:"));
	i = 1;
	while (var[i] && &var[i] != eovn)
	{
		if (var[i] == '+' && var[i + 1] == '=')
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (export_error(var, eovn, err_occ,
					"not a valid identifier:"));
		i++;
	}
	return (1);
}

int	var_exist(char *var, int *mod, char **envp)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (ft_strchr(var, '=') && (*(ft_strchr(var, '=') - 1)) == '+')
		*mod = APPEND;
	i = 0;
	while (envp[i])
	{
		j = 0;
		k = 0;
		while (var[j] && var[j] != '+' && var[j] != '=')
		{
			if (var[j] != envp[i][k])
				break ;
			j++;
			k++;
		}
		if (j > 0 && k > 0 && var[j - 1] == envp[i][k - 1])
			return (1);
		i++;
	}
	return (0);
}

void	check_export_delimiter(size_t *j, size_t *i, size_t *k, char *var)
{
	char	**envp;

	envp = envp_handler(GETENV, NULL);
	while (var[*j] != '+' && var[*j] != '=')
	{
		if (var[*j] != envp[*i][*k])
			break ;
		(*j)++;
		(*k)++;
	}
}

void	append_env_var(char *var, char **envp)
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
		check_export_delimiter(&j, &i, &k, var);
		if (var[j] == '+')
			j++;
		if (var[j] == envp[i][k] || !envp[i][k])
		{
			eovn = envp[i];
			if (envp[i][k])
				j++;
			envp[i] = ft_strjoin(envp[i], &var[j]);
			free(eovn);
			return ;
		}
		i++;
	}
}
