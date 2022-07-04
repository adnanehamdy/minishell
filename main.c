/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/07/04 17:37:05 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	here_doc_flag(int mod)
{
	static int	flag;

	if (mod)
		flag = mod;
	return (flag);
}

void	ctrl_c_handler(int signal)
{
	(void)signal;
	ft_fprintf(STANDARD_OUTPUT, "\n");
	if (here_doc_flag(GET_FLAG) == HERE_DOC_FLAG)
	{
		here_doc_flag(HERE_DOC_FLAG_SIGINT);
		close(0);
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_code_handler(POSTEXIT, 130);
}

static void	minishell_routine( void )
{
	char			*prompt_cmd;
	t_cmd_line		**cmd_line;

	prompt_cmd = readline("\033[0;35mminishell> \033[0;37m");
	if (!prompt_cmd)
	{
		ft_fprintf(STANDARD_ERROR, "exit\n");
		exit(exit_code_handler(GETEXIT, 0));
	}
	cmd_line = parsing_functions(prompt_cmd);
	if (here_doc_flag(GET_FLAG) == HERE_DOC_FLAG_SIGINT)
	{
		here_doc_flag(DEFAULT_FLAG);
		return ;
	}
	if (cmd_line)
	{
		exit_code_handler(POSTEXIT, execute_cmd_line(cmd_line));
	}
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
	while (MINISHELL_IS_RUNNING)
		minishell_routine();
	return (0);
}
