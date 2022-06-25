/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/25 05:59:26 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ctrl_c_handler(int signal)
{

	(void)signal;
	rl_on_new_line();
	rl_replace_line("\n", 0);
	rl_redisplay();
	return ;
}

void	ctrl_backslash_handler(int signal)
{
	(void)signal;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	return ;
}

int main(int c, char **v, char **envp)
{
	t_cmd_line		**cmd_line;
	char			*prompt_cmd;

	(void)v;
	if (c != 1)
		return (1);
	envp_handler(POSTENV, env_dup(envp));
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_backslash_handler);
	while (1)
	{
		prompt_cmd = readline("\033[0;35mminishell> \033[0;37m");
		if (!prompt_cmd)
		{
			printf("exit\n");
			return (exit_code_handler(GETEXIT, 0));
		}
		cmd_line = parsing_functions(prompt_cmd);
		if (cmd_line)
		{
			exit_code_handler(POSTEXIT, execute_cmd_line(cmd_line));
			add_history(prompt_cmd);
		}
		free(prompt_cmd);
	}
	return (0);
}
