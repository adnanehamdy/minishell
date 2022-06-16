/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:32:35 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 17:56:32 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char	*fd_fail_msg(char *file)
// {
// 	char	*msg;

// 	if (!access(file, F_OK))
// 		msg = ft_strjoin("pipex : permission denied :",
// 				file);
// 	else
// 	{
// 		msg = ft_strjoin("pipex : no such file or directory :",
// 				file);
// 	}
// 	return (msg);
// }

static void	exit_cmd_msg(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

static char	*cmd_path(char *tmp, char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	return (tmp);
}

static char	**setup_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			break;
		i++;
	}
	if (!envp[i])
		return (0);
	return (ft_split(&envp[i][5], ':'));
}

char	*allocate_cmd_path(char	**envp, char *cmd)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	path = setup_path(envp);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!(access(tmp2, X_OK)))
			return (cmd_path(tmp2, path));
		else
			free(tmp2);
		i++;
	}
	exit_cmd_msg(path);
	return (0);
}