/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:56:16 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 18:46:19 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	structlen(t_cmd_line **cmd_line)
{
	size_t len;

	len = 0;
	while (cmd_line[len])
		len++;
	return (len);
}

static void	run_command(t_cmd_line *cmd_line)
{
	pid_t	pid;

	if (cmd_line->in < 0 || cmd_line->out < 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (!pid)
	{
		if (cmd_line->in != 0)
			dup2(cmd_line->in, STANDARD_INPUT);
		if (cmd_line->out != 1)
			dup2(cmd_line->out, STANDARD_OUTPUT);
		if (cmd_line->in != 0)
			close(cmd_line->in);
		if (cmd_line->out != 1)
			close(cmd_line->out);
		if (execve(cmd_line->cmd_path, cmd_line->command, envp_handler(GETENV, NULL)) < 0)
			perror("Error");
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