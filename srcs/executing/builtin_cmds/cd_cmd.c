/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:12:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 17:53:04 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_home_env(void)
{
	size_t	i;
	char	**env;

	env = envp_handler(GETENV, 0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("HOME=", env[i], 5))
			return (env[i]);
		i++;
	}
	return (0);
}

static int	change_directory(t_cmd_line *cmd, char *home)
{
	if (cmd->command[1])
	{
		if (chdir(cmd->command[1]) < 0)
		{
			ft_fprintf(STANDARD_ERROR,
				"minishell: cd: %s: No such file or directory\n",
				cmd->command[1]);
			return (1);
		}
	}
	else
	{
		if (!home || chdir(&home[5]) < 0)
		{
			ft_fprintf(STANDARD_ERROR, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	return (0);
}

static void	setup_pwd_var(char *keyword, char **envp, int first)
{
	char	**pwd_var;
	char	*tmp;
	char	*work_dir;

	work_dir = getcwd(NULL, 0);
	pwd_var = get_env_var(keyword, envp, first);
	if (work_dir && pwd_var)
	{
		free(*pwd_var);
		tmp = ft_strjoin(keyword, "=");
		*pwd_var = ft_strjoin(tmp, work_dir);
		free(tmp);
	}
	if (work_dir)
		free(work_dir);
}

int	cd_command(t_cmd_line *cmd)
{
	char		*home;
	static int	first;

	home = get_home_env();
	setup_pwd_var("OLDPWD", envp_handler(GETENV, NULL), first);
	first = 1;
	if (change_directory(cmd, home))
		return (1);
	setup_pwd_var("PWD", envp_handler(GETENV, NULL), 1);
	return (0);
}
