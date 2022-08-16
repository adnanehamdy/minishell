/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:56:16 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/16 18:00:57 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_error_handler(t_cmd_line *cmd_line)
{
	if (cmd_line->is_executable == PERMISSION_DENIED)
	{
		ft_putstr_fd("minishell: permission denied: ", STANDARD_ERROR);
		ft_putendl_fd(cmd_line->command[0], STANDARD_ERROR);
		exit(126);
	}
	else if (cmd_line->is_executable == NO_SUCH_FILE)
	{
		ft_putstr_fd("minishell: no such file or directory: ", STANDARD_ERROR);
		ft_putendl_fd(cmd_line->command[0], STANDARD_ERROR);
	}		
	else
	{
		ft_putstr_fd("minishell: command not found: ", STANDARD_ERROR);
		ft_putendl_fd(cmd_line->command[0], STANDARD_ERROR);
	}
	exit(127);
}

static void	config_redir(t_cmd_line **cmds, t_cmd_line *cmd_line)
{
	int	i;

	if (cmd_line->in != 0)
	{
		dup2(cmd_line->in, STANDARD_INPUT);
		close(cmd_line->in);
	}
	if (cmd_line->out != 1)
	{
		dup2(cmd_line->out, STANDARD_OUTPUT);
		close(cmd_line->out);
	}
	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]->in)
			close(cmds[i]->in);
		if (cmds[i]->out != 1)
			close(cmds[i]->out);
	}
}

static void	run_child_command(t_cmd_line **cmd,
	t_cmd_line *cmd_line, int pipeline)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	config_redir(cmd, cmd_line);
	if (!run_builtin(cmd_line, pipeline))
		exit(0);
	if (execve(cmd_line->cmd_path, cmd_line->command,
			envp_handler(GETENV, NULL)) < 0)
		exec_error_handler(cmd_line);
}

static pid_t	run_command(t_cmd_line **cmd,
					t_cmd_line *cmd_line, int pipeline)
{
	pid_t	pid;

	if (cmd_line->in < 0 || cmd_line->out < 0)
	{
		if (cmd_line->in > 0)
			close(cmd_line->in);
		if (cmd_line->out > 1)
			close(cmd_line->out);
		return (-1);
	}
	if (!pipeline && !run_builtin(cmd_line, pipeline))
		return (-1);
	pid = fork();
	if (pid < 0)
		return (pid);
	if (!pid)
		run_child_command(cmd, cmd_line, pipeline);
	signal(SIGINT, SIG_IGN);
	if (cmd_line->in != 0)
		close(cmd_line->in);
	if (cmd_line->out != 1)
		close(cmd_line->out);
	return (pid);
}

int	execute_cmd_line(t_cmd_line **cmd_line)
{
	size_t	index;
	int		more;
	int		exit_code;
	int		ret_exit;
	pid_t	pid;

	index = 0;
	exit_code = 0;
	more = 0;
	if (cmd_line[index + 1])
		more = 1;
	while (cmd_line[index])
		pid = run_command(cmd_line, cmd_line[index++], more);
	ret_exit = 0;
	more = 0;
	while (more != -1)
	{
		more = wait(&exit_code);
		if (more == pid)
			ret_exit = exit_code;
	}
	free_cmd_line(cmd_line);
	signal(SIGINT, ctrl_c_handler);
	if (WIFSIGNALED(ret_exit) == 1)
		return (130);
	return (WEXITSTATUS(ret_exit));
}
