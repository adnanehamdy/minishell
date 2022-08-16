/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:44:35 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/16 08:15:15 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<minishell.h>

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
	while (prompt_cmd[i])
	{
		if (prompt_cmd[i] == '"')
		{
			if (check_second_quote(&prompt_cmd[i], '"') == -1)
				break ;
			i = i + check_second_quote(&prompt_cmd[i], '"');
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
	if ((prompt_cmd[*index] == '<' || prompt_cmd[*index] == '>'
			|| prompt_cmd[*index] == '|') && prompt_cmd[0] != '|')
	{
		if (prompt_cmd[(*index) + 1] != prompt_cmd[*index]
			|| ((prompt_cmd[(*index) + 1] == prompt_cmd[*index])
				&& prompt_cmd[*index] == '|'))
			ft_fprintf(STANDARD_ERROR,
				"minishell: syntax error near unexpected token '%c'\n",
				prompt_cmd[*index]);
		else
			ft_fprintf(STANDARD_ERROR,
				"minishell: syntax error near unexpected token '%c%c'\n",
				prompt_cmd[*index], prompt_cmd[*index]);
		exit_code_handler(POSTEXIT, 258);
		return (0);
	}
	else if ((prompt_cmd[*index] == '|' && prompt_cmd[0] == prompt_cmd[*index]))
	{
		ft_fprintf(STANDARD_ERROR,
			"minishell: syntax error near unexpected token '%c'\n",
			prompt_cmd[*index]);
		exit_code_handler(POSTEXIT, 258);
		return (0);
	}
	return (1);
}

int	check_pipe(char *prompt_cmd)
{
	int	index;

	index = 0;
	while (prompt_cmd[index] && ((prompt_cmd[index] >= 9
				&& prompt_cmd[index] <= 13) || (prompt_cmd[index] == ' ')))
			index++;
	if (prompt_cmd[index] == '|' || prompt_cmd[0] == '|')
	{
		ft_fprintf(STANDARD_ERROR,
			"minishell: syntax error near unexpected token '%c'\n",
			prompt_cmd[index]);
		exit_code_handler(POSTEXIT, 258);
		return (-1);
	}
	return (0);
}

void	check_separators(char *prompt_cmd)
{
	int	index;

	index = 0;
	check_pipe(prompt_cmd);
	if (exit_code_handler(GETENV, 0))
		return ;
	while (prompt_cmd[index])
	{
		if (prompt_cmd[index] == '"')
			index = index + check_second_quote(&prompt_cmd[index], '"');
		else if (prompt_cmd[index] == '\'')
			index = index + check_second_quote(&prompt_cmd[index], '\'');
		if (prompt_cmd[index] == '<'
			|| prompt_cmd[index] == '>' || prompt_cmd[index] == '|')
		{
			if (prompt_cmd[index + 1]
				&& prompt_cmd[index + 1] == prompt_cmd[index]
				&& prompt_cmd[index] != '|')
					index = index + 1;
			if (skip_white_spaces(&prompt_cmd[index], 1) < 0)
				break ;
		}
		index++;
	}
}
