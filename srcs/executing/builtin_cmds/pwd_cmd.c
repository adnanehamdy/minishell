/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:46:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 17:54:13 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_env_var(char *kw, char **envp, int first)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (first)
		tmp = ft_strjoin(kw, "=");
	else
		tmp = kw;
	while (envp && envp[i] && ft_strncmp(tmp, envp[i], ft_strlen(tmp)))
		i++;
	if (tmp != kw)
		free(tmp);
	if (envp && envp[i])
		return (&envp[i]);
	return (NULL);
}

int	pwd_command(t_cmd_line *cmd)
{
	char			*pwd;
	char			**pwd_var;
	static char		*reserve;

	if (!reserve)
	{
		pwd_var = get_env_var("PWD", envp_handler(GETENV, NULL), 1);
		if (pwd_var && *pwd_var)
			reserve = ft_strdup(&(*pwd_var)[4]);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = reserve;
	else
	{
		if (reserve)
			free(reserve);
		reserve = pwd;
	}
	ft_fprintf(cmd->out, "%s\n", pwd);
	return (0);
}
