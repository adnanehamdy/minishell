/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:56:16 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 09:18:33 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	config_redir(t_cmd_line **cmds, t_cmd_line *cmd_line)
{
	int	i;

	if (cmd_line->in != 0)
		dup2(cmd_line->in, STANDARD_INPUT);
	if (cmd_line->out != 1)
		dup2(cmd_line->out, STANDARD_OUTPUT);
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
	if (!run_builtin(cmd_line, pipeline))
		exit(0);
	config_redir(cmd, cmd_line);
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

static int	convert_signal_to_exit_code(int ret_exit)
{
	if (WIFSIGNALED(ret_exit))
	{
		if (WTERMSIG(ret_exit) == 2)
			return (130);
		if (WTERMSIG(ret_exit) == 3)
			return (131);
	}
	return (WEXITSTATUS(ret_exit));
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
	return (convert_signal_to_exit_code(ret_exit));
}
