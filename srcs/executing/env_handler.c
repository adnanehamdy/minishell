/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:11:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 18:03:53 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**envp_handler(int mod, char **new_envp)
{
	static char	**envp;

	if (mod)
		envp = new_envp;
	return (envp);
}

static int	check_pwd_exist(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PWD=", envp[i], 4))
			return (0);
		i++;
	}
	return (1);
}

char	**env_dup(char	**envp)
{
	char	**new_envp;
	char	*gcwd;
	int		pwd_exist;
	size_t	len;

	len = ptrlen(envp);
	pwd_exist = check_pwd_exist(envp);
	new_envp = (char **)malloc(sizeof(char *) * (len + pwd_exist + 2));
	len = 0;
	while (envp[len])
	{
		new_envp[len] = ft_strdup(envp[len]);
		len++;
	}
	if (pwd_exist)
	{
		gcwd = getcwd(NULL, 0);
		new_envp[len++] = ft_strjoin("PWD=", gcwd);
		if (gcwd)
			free(gcwd);
	}
	new_envp[len++] = ft_strdup("OLDPWD");
	new_envp[len] = 0;
	return (new_envp);
}
