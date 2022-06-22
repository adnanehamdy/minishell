/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/22 07:38:43 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	singint_handler(int signal)
{
	if (signal == SIGINT)
		printf("\n\033[0;35mminishell> \033[0;37m");
	return ;
}

// void

int main(int c, char **v, char **envp)
{
	t_cmd_line	**cmd_line;
	char		*prompt_cmd;

	(void)c;
	(void)v;
	envp_handler(POSTENV, env_dup(envp));
	signal(SIGINT, singint_handler);
	while (1)
	{
		prompt_cmd = readline("\033[0;35mminishell> \033[0;37m");
		if (!prompt_cmd)
		{
			printf("\n");
			return (exit_code_handler(GETEXIT, 0));
		}
		add_history(prompt_cmd);
		cmd_line = parsing_functions(prompt_cmd);
		if (cmd_line)
			exit_code_handler(POSTEXIT, execute_cmd_line(cmd_line));
		// free(prompt_cmd);
	}
	return (0);
}