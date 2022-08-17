/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/17 11:09:08 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ctrl_c_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	exit_code_handler(POSTEXIT, 1);
}

static void	minishell_routine(void)
{
	t_cmd_line		**cmd_line;
	char			*prompt_cmd;

	prompt_cmd = readline("minishell> ");
	if (!prompt_cmd)
	{
		ft_fprintf(STANDARD_ERROR, "exit\n");
		exit(exit_code_handler(GETEXIT, 0));
	}
	if (!(*prompt_cmd))
		return ;
	cmd_line = parsing_functions(prompt_cmd);
	if (here_doc_signal(0, 0))
	{
		here_doc_signal(1, 0);
		exit_code_handler(POSTEXIT, 1);
		add_history(prompt_cmd);
		free_cmd_line(cmd_line);
		free(prompt_cmd);
		return ;
	}
	if (cmd_line)
		exit_code_handler(POSTEXIT, execute_cmd_line(cmd_line));
	add_history(prompt_cmd);
	free(prompt_cmd);
}

int	main(int c, char **v, char **envp)
{
	(void)v;
	if (c != 1)
		return (1);
	envp_handler(POSTENV, env_dup(envp));
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		minishell_routine();
	return (0);
}
