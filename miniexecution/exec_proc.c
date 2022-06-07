/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:56:16 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/06 17:50:40 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	static	int	old_read_fd;
	int		fd[2];
	char	*command_path;
	pid_t	pid;

	if (cmd_line->in < 0 || cmd_line->out < 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (!pid)
	{
		if (execve(cmd_line->cmd_path, cmd_line->command, cmd_line->envp) < 0)
			perror("Error");
	}
	close(cmd_line->in);
	close(cmd_line->out);
}

int	execute_cmd_line(t_cmd_line **cmd_lines)
{
	size_t	index;
	int		exit_code;

	index = 0;
	exit_code = 0;
	while (cmd_lines[index])
		run_command(cmd_lines[index++]);
	while (wait(&exit_code) != -1)
		;
	return (exit_code);
}