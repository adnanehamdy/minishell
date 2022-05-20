/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 07:19:08 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/18 08:23:23 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code_handler(int mod, int value)
{
	static int exit_code;
	
	if (mod == GETEXIT)
		return exit_code;
	else if (mod == POSTEXIT)
		exit_code = value;
	return (0);
}

int	check_second_quote(char *sub_prompt_cmd, char quote)
{
	int	index;

	index = 1;
	while (sub_prompt_cmd[index])
	{
		if (sub_prompt_cmd[index] == quote)
			return (index);
		index++;
	}
	printf("unclosed quote\n");
	exit_code_handler(POSTEXIT, 1);
	return (-1);
}

void	check_quotes(char *prompt_cmd)
{
	int	i;

	i = 0;
	while (i != -1  && prompt_cmd[i])
	{
		if (prompt_cmd[i] == '"')
		{
			if (check_second_quote(&prompt_cmd[i] , '"') == -1)
				break ;
			i = i + check_second_quote(&prompt_cmd[i] , '"');
		}
		else if (prompt_cmd[i] == '\'')
		{
			if (check_second_quote(&prompt_cmd[i], '\'') == -1)
				break ;
			i = i + check_second_quote(&prompt_cmd[i], '\'');
		}
		i++;
	}
}
int	skip_white_spaces(char *prompt_cmd, int condition)
{
	int	index;

	index = 1;
	while (prompt_cmd[index])
	{
		if ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13) || (prompt_cmd[index] == ' '))
			index++;
		else
			break ;
	}
	if (prompt_cmd[index] && condition)
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>' || prompt_cmd[index] == '|')
		{
 			if (prompt_cmd[index + 1] != prompt_cmd[index])
				printf("\033[0;35mminishell> \033[0;37msyntax error near unexpected token '%c'\n", prompt_cmd[index]);
			else
				printf("\033[0;35mminishell> \033[0;37msyntax error near unexpected token '%c%c'\n", prompt_cmd[index], prompt_cmd[index]);
			exit_code_handler(POSTEXIT, 258);
			return (-1);
		}
	}
	if (!prompt_cmd[index] && condition)
	{
			if (prompt_cmd[index - 1] == '<' || prompt_cmd[index - 1] == '>' || prompt_cmd[index - 1] == '|')
			{
				printf("\033[0;35mminishell> \033[0;37msyntax error near unexpected token 'newline'\n");
				exit_code_handler(POSTEXIT, 258);
				return (-1);
			}
	}
	return (index);
}

void	check_separators(char *prompt_cmd)
{
	int	index;

	index = 0;
	while (prompt_cmd[index])
	{
		if (prompt_cmd[index] == '"')
			index = index + check_second_quote(&prompt_cmd[index], '"');
		else if (prompt_cmd[index] == '\'')
			index = index + check_second_quote(&prompt_cmd[index], '\'');
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>' || prompt_cmd[index] == '|')
		{
			if (prompt_cmd[index + 1] && prompt_cmd[index + 1] == prompt_cmd[index] && prompt_cmd[index] != '|')
				index = index + 1;
 			if (skip_white_spaces(&prompt_cmd[index], 1) < 0)
				break ;
		}
		index++;
	}
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
		if (prompt_cmd[index] == ';' || prompt_cmd[index] == '&' || prompt_cmd[index] == '\\')
		{
			printf("\033[0;35mminishell> \033[0;37msyntax error near unexpected token '%c'\n", prompt_cmd[index]);
			exit_code_handler(POSTEXIT, 258);
		}
		index++;
	}	
}

void	error_checker(char *prompt_cmd)
{
	check_quotes(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 1))
 		invalid_special_character(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 1))
		check_separators(prompt_cmd);
}