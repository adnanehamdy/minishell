/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:56:16 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/16 19:11:44 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	structlen(t_cmd_line **cmd_line)
{
	size_t	len;

	len = 0;
	while (cmd_line[len])
		len++;
	return (len);
}

static void	exec_error_handler(t_cmd_line *cmd_line)
{
	if (cmd_line->is_executable < 0)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(cmd_line->command[0], 2);
		exit(126);
	}
	if (cmd_line->cmd_path)
		ft_putstr_fd("minishell: no such file or directory: ", 2);
	else
		ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd_line->command[0], 2);
	exit(127);
}

static void	config_redir(t_cmd_line *cmd_line)
{
	if (cmd_line->in != 0)
		dup2(cmd_line->in, STANDARD_INPUT);
	if (cmd_line->out != 1)
		dup2(cmd_line->out, STANDARD_OUTPUT);
	if (cmd_line->in != 0)
		close(cmd_line->in);
	if (cmd_line->out != 1)
		close(cmd_line->out);
}

static void	run_command(t_cmd_line *cmd_line)
{
	pid_t	pid;

	if (cmd_line->in < 0 || cmd_line->out < 0)
		return ;
	if (!run_builtin(cmd_line))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (!pid)
	{
		config_redir(cmd_line);
		if (execve(cmd_line->cmd_path, cmd_line->command,
				envp_handler(GETENV, NULL)) < 0)
			exec_error_handler(cmd_line);
	}
	if (cmd_line->in != 0)
		close(cmd_line->in);
	if (cmd_line->out != 1)
		close(cmd_line->out);
}

int	execute_cmd_line(t_cmd_line **cmd_line)
{
	size_t	index;
	int		exit_code;

	index = 0;
	exit_code = 0;
	while (cmd_line[index])
		run_command(cmd_line[index++]);
	while (wait(&exit_code) != -1)
		;
	return (exit_code);
}
