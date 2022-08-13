/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 07:19:08 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/02 05:46:02 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_code_handler(int mod, int value)
{
	static int	exit_code;

	if (mod == POSTEXIT)
		exit_code = value;
	return (exit_code);
}

int	check_unexpected_newline(void)
{
	ft_fprintf(STANDARD_ERROR,
		"minishell: syntax error near unexpected token 'newline'\n");
	exit_code_handler(POSTEXIT, 258);
	return (0);
}

int	skip_white_spaces(char *prompt_cmd, int condition)
{
	int	index;

	index = 1;
	while (prompt_cmd[index])
	{
		if ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13)
			|| (prompt_cmd[index] == ' '))
			index++;
		else
			break ;
	}
	if (prompt_cmd[index] && condition)
	{
		if (!check_unexpected_token(prompt_cmd, &index))
			return (-1);
	}
	if (!prompt_cmd[index] && condition)
	{
		if (!check_unexpected_newline())
			return (-1);
	}
	return (index);
}

void	invalid_special_character(char *prompt_cmd)
{
	int	index;

	index = 0;
	while (prompt_cmd[index])
	{
		if (prompt_cmd[index] == '"')
			index = index + check_second_quote(&prompt_cmd[index], '"');
		else if (prompt_cmd[index] == '\'')
			index = index + check_second_quote(&prompt_cmd[index], '\'');
		if (prompt_cmd[index] == ';'
			|| prompt_cmd[index] == '&' || prompt_cmd[index] == '\\')
		{
			ft_fprintf(STANDARD_ERROR,
				"minishell: syntax error near unexpected token '%c'\n",
				prompt_cmd[index]);
			exit_code_handler(POSTEXIT, 258);
			return ;
		}
		index++;
	}	
}

int	error_checker(char *prompt_cmd)
{
	int	exit_status;

	exit_status = exit_code_handler(GETEXIT, 0);
	exit_code_handler(POSTEXIT, 0);
	check_quotes(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 0))
		invalid_special_character(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 0))
		check_separators(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 0))
		check_max_here_doc(prompt_cmd);
	return (exit_status);
}
