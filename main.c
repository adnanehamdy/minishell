/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/13 18:38:44 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"



int main(int c, char **v, char **envp)
{
	t_cmd_line	**cmd_line;
	char		*prompt_cmd;

	(void)c;
	(void)v;
	envp_handler(POSTENV, env_dup(envp));
	while (1)
	{
		prompt_cmd = readline("\033[0;35mminishell> \033[0;37m");
		add_history(prompt_cmd);
		cmd_line = parsing_functions(prompt_cmd);
		if (cmd_line)
			execute_cmd_line(cmd_line);
		free(prompt_cmd);
	}
}