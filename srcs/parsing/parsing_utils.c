/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:10:16 by ahamdy            #+#    #+#             */
/*   Updated: 2022/08/17 21:04:02 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_cmd_number(char *prompt_cmd)
{
	int	number;
	int	index;

	index = 0;
	number = 1;
	while (prompt_cmd[index])
	{
		if (prompt_cmd[index] == '"')
			index = index + check_second_quote(&prompt_cmd[index], '"');
		else if (prompt_cmd[index] == '\'')
			index = index + check_second_quote(&prompt_cmd[index], '\'');
		if (prompt_cmd[index] == '|')
			number++;
		index++;
	}
	return (number);
}

int	cmd_len(char *prompt_cmd)
{
	int	index;
	int	number;

	number = 0;
	index = 0;
	while (prompt_cmd[index])
	{
		if (prompt_cmd[index] == '"' || prompt_cmd[index] == '\'')
			index++;
		else
		{
			index++;
			number++;
		}
	}
	return (number);
}

char	*sub_cmd(char *prompt_cmd, int start, int len)
{
	char	*cmd;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!prompt_cmd)
		return (0);
	if (start > cmd_len(prompt_cmd))
		count = 1;
	else if (cmd_len(prompt_cmd) > (len + start))
		count = len + 1;
	else if (cmd_len(prompt_cmd) <= (len + start))
		count = cmd_len(prompt_cmd) - (start) + 1;
	cmd = (char *)malloc(count);
	if (!cmd)
		return (0);
	while (count > 1 && len-- && prompt_cmd[start])
		cmd[i++] = prompt_cmd[start++];
	cmd[i] = 0;
	return (cmd);
}

// int	check_redirection(char **cmd, int *index, char last_char, int is_first)
// {
// 	if ((*cmd)[*index] == '"' || (*cmd)[*index] == '\'')
// 		index = index + check_second_quote(&(*cmd)[*index],
// 				(*cmd)[*index]);
// 	return (expand_redirection(cmd, index, last_char, is_first));
// }

int	skip_quote(char *cmd, int *index)
{
	if (cmd && cmd[*index] && cmd[*index] == '\'')
	{
		*index = *index + check_second_quote(&cmd[*index], '\'');
		(*index)++;
		return (0);
	}
	return (1);
}
