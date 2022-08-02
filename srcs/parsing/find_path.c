/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:32:35 by nelidris          #+#    #+#             */
/*   Updated: 2022/07/31 03:37:44 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*allocate_cmd_path(t_cmd_line *command, char	**envp, char *cmd)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	if (cmd && ft_strchr(cmd, '/'))
	{
		if (!(access(cmd, F_OK)))
		{
			if (access(cmd, X_OK) < 0)
				command->is_executable = PERMISSION_DENIED;
		}
		else
			command->is_executable = NO_SUCH_FILE;
		return (ft_strdup(cmd));
	}
	path = setup_path(envp);
	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!(access(tmp2, F_OK)))
		{
			if (access(tmp2, X_OK) < 0)
				command->is_executable = PERMISSION_DENIED;
			else
				command->is_executable = NO_SUCH_FILE;
			return (cmd_path(tmp2, path));
		}
		else
			free(tmp2);
		i++;
	}
	exit_cmd_msg(path);
	return (0);
}