/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_alloc_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:49:44 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/23 23:35:09 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_count_arg_number(char *prompt_cmd, int *index)
{
	while (prompt_cmd[*index]
		&& ((prompt_cmd[*index] < 9 || prompt_cmd[*index] > 13)
		&& prompt_cmd[*index] != ' ') && prompt_cmd[*index] != '<'
		&& prompt_cmd[*index] != '>' && prompt_cmd[*index] != '|')
	{
		if (prompt_cmd[*index] == '"')
			*index = *index + check_second_quote(&prompt_cmd[*index], '"');
		else if (prompt_cmd[*index] == '\'')
			*index = *index + check_second_quote(&prompt_cmd[*index], '\'');
		(*index)++;
	}
}
int	sub_count_each_arg(char *prompt_cmd, int *index, int *number)
{
	int tmp;

	tmp = 0;
	while (prompt_cmd[*index]
		&& ((prompt_cmd[*index] < 9 || prompt_cmd[*index] > 13)
			&& prompt_cmd[*index] != ' ') && prompt_cmd[*index] != '<'
		&& prompt_cmd[*index] != '>' && prompt_cmd[*index] != '|')
	{
		if (prompt_cmd[*index] == '"')
		{
			tmp = *index;
			*index = *index + check_second_quote(&prompt_cmd[*index], '"');
			*number = *number + (*index - tmp - 1);
		}
		else if (prompt_cmd[*index] == '\'')
		{
			tmp = *index;
			*index = *index + check_second_quote(&prompt_cmd[*index], '\'');
			*number = *number + (*index - tmp - 1);
		}
		else
			(*number)++;
		(*index)++;
	}
	return (*number);
}

void	second_sub_fill_arg(char *cmd_arg, char *cmd, int *index, int *i)
{
	char quote;

	quote = cmd[*index];
	(*index)++;
	while (cmd[*index] != quote)
	{
		cmd_arg[*i] = cmd[*index];
		(*i)++;
		(*index)++;
	}
}

char	*sub_fill_each_arg(char *cmd_arg, char *prompt_cmd, int *index)
{
	int	i;

	i = 0;
	while (prompt_cmd[*index]
		&& ((prompt_cmd[*index] < 9 || prompt_cmd[*index] > 13)
			&& prompt_cmd[*index] != ' ') && prompt_cmd[*index] != '<'
		&& prompt_cmd[*index] != '>' && prompt_cmd[*index] != '|')
	{
		if (prompt_cmd[*index] == '"')
			second_sub_fill_arg(cmd_arg, prompt_cmd,
				index, &i);
		else if (prompt_cmd[*index] == '\'')
			second_sub_fill_arg(cmd_arg, prompt_cmd,
				index, &i);
		else
		{
			cmd_arg[i] = prompt_cmd[*index];
			i++;
		}
		(*index)++;
	}
	cmd_arg[i] = 0;
	return (cmd_arg);
}

int	count_io_redirection(char *prompt_cmd)
{
	int	index;
	int	number;

	index = 0;
	number = 0;
	while (prompt_cmd[index] && prompt_cmd[index] != '|')
	{
		if (prompt_cmd[index] == '<' || prompt_cmd[index] == '>')
		{
			if (prompt_cmd[index + 1] == prompt_cmd[index])
				index = index + 1;
			number++;
		}
		index++;
	}
	return (number);
}