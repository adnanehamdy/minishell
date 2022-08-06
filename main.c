/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/06 15:03:44 by nelidris         ###   ########.fr       */
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
}

static void	minishell_routine(void)
{
	t_cmd_line		**cmd_line;
	char			*prompt_cmd;

	prompt_cmd = readline("\033[0;35mminishell> \033[0;37m");
	if (!prompt_cmd)
	{
		ft_fprintf(STANDARD_ERROR, "exit\n");
		exit(exit_code_handler(GETEXIT, 0));
	}
	if (!(*prompt_cmd))
		return ;
	cmd_line = parsing_functions(prompt_cmd);
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
