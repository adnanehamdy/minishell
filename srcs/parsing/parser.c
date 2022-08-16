/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/14 14:36:39 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd_line	**parse_data(char *prompt_cmd)
{
	int	cmd_number;

	cmd_number = count_cmd_number(prompt_cmd);
	return (initialize_cmd_line(prompt_cmd, cmd_number));
}

t_cmd_line	**parsing_functions(char *prompt_cmd)
{
	int	exit_status;

	exit_status = error_checker(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 0) && prompt_cmd[0])
	{
		exit_code_handler(POSTEXIT, exit_status);
		return (parse_data(prompt_cmd));
	}
	return (0);
}

void	ctrl_c_here_doc_handler(int signal)
{
	(void)signal;
	here_doc_signal(1, 1);
	close(0);
	write(1, "\n", 1);
}

int	here_doc_signal(int mod, int value)
{
	static int	sig;

	if (mod)
		sig = value;
	return (sig);
}

void	quote_skip(char *cmd, int *index)
{
	if (cmd[*index] == '"')
	{
		*index = *index + check_second_quote(&cmd[*index], '"');
		*index = *index + 1;
	}
	else if (cmd[*index] == '\'')
	{
		*index = *index + check_second_quote(&cmd[*index], '\'');
		*index = *index + 1;
	}
}
