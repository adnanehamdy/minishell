/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 07:19:08 by ahamdy            #+#    #+#             */
/*   Updated: 2022/07/05 01:30:35 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_code_handler(int mod, int value)
{
	static int exit_code;
	if (mod == POSTEXIT)
		exit_code = value;
	return (exit_code);
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
	ft_fprintf(STANDARD_ERROR, "unclosed quote\n");
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

int	check_unexpected_token(char *prompt_cmd, int *index)
{
	if ((prompt_cmd[*index] == '<' || prompt_cmd[*index] == '>' || prompt_cmd[*index] == '|') && prompt_cmd[0] != '|')
	{
		if (prompt_cmd[(*index) + 1] != prompt_cmd[*index] || ((prompt_cmd[(*index) + 1] == prompt_cmd[*index]) && prompt_cmd[*index] == '|'))
			ft_fprintf(STANDARD_ERROR, "minishell: syntax error near unexpected token '%c'\n", prompt_cmd[*index]);
		else
			ft_fprintf(STANDARD_ERROR, "minishell: syntax error near unexpected token '%c%c'\n", prompt_cmd[*index], prompt_cmd[*index]);
		exit_code_handler(POSTEXIT, 258);
		return (0);
	}
	else
		if ((prompt_cmd[*index] == '|' && prompt_cmd[0] == '|'))
		{
			ft_fprintf(STANDARD_ERROR, "minishell: syntax error near unexpected token '%c'\n", prompt_cmd[*index]);
			exit_code_handler(POSTEXIT, 258);
			return (0);
		}
		return (1);
}

int	check_unexpected_newline(void)
{
	ft_fprintf(STANDARD_ERROR, "minishell: syntax error near unexpected token 'newline'\n");
	exit_code_handler(POSTEXIT, 258);
	return (0);
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

int		check_pipe(char *prompt_cmd)
{
	int	index;

	index = 0;
	while (prompt_cmd[index] && ((prompt_cmd[index] >= 9 && prompt_cmd[index] <= 13) || (prompt_cmd[index] == ' ')))
			index++;
	if (prompt_cmd[index] == '|')
	{
		ft_fprintf(STANDARD_ERROR, "minishell: syntax error near unexpected token '%c'\n", prompt_cmd[index]);
		exit_code_handler(POSTEXIT, 258);
		return (-1);
	}
	return (0);
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
	check_pipe(prompt_cmd);
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
			ft_fprintf(STANDARD_ERROR, "minishell: syntax error near unexpected token '%c'\n", prompt_cmd[index]);
			exit_code_handler(POSTEXIT, 258);
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
	return (exit_status);
}