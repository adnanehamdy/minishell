/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:11:52 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 16:28:34 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**envp_handler(int mod, char **new_envp)
{
	static char	**envp;

	if (mod)
		envp = new_envp;
	return (envp);
}

char	**env_dup(char	**envp)
{
	char	**new_envp;
	size_t	len;

	len = ptrlen(envp);
	new_envp = (char **)malloc(sizeof(char*) * (len + 1));
	len = 0;
	while (envp[len])
	{
		new_envp[len] = ft_strdup(envp[len]);
		len++;
	}
	new_envp[len] = 0;
	return (new_envp);
}