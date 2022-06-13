/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_alloc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:45:55 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/13 15:50:56 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_io_redirection(char *sub_prompt_cmd)
{
	int	index;

	index = 0;
	while (sub_prompt_cmd[index] && sub_prompt_cmd[index] != '|')
	{
		if ((sub_prompt_cmd[index] >= 9 && sub_prompt_cmd[index] <= 13)
			|| sub_prompt_cmd[index] == ' ' || sub_prompt_cmd[index] == '<'
			|| sub_prompt_cmd[index] == '>')
			break ;
		if (sub_prompt_cmd[index] == '"')
			index = index + check_second_quote(&sub_prompt_cmd[index], '"');
		else if (sub_prompt_cmd[index] == '\'')
			index = index + check_second_quote(&sub_prompt_cmd[index], '\'');
		index++;
	}
	return (index);
}

// int	skip_argument(char *prompt_cmd, int *index)
// {
// 	while (prompt_cmd[*index]
// 		&& ((prompt_cmd[*index] < 9 && prompt_cmd[*index] > 13)
// 			|| prompt_cmd[*index] != ' ') && prompt_cmd[*index] != '<'
// 		&& prompt_cmd[*index] != '>' && prompt_cmd[*index] != '|')
// 	{
// 		if (prompt_cmd[*index] == '"')
// 			*index = *index + check_second_quote(&prompt_cmd[*index], '"');
// 		else if (prompt_cmd[*index] == '\'')
// 			*index = *index + check_second_quote(&prompt_cmd[*index], '\'');
// 		(*index) = (*index) + 1;
// 	}
// 	return (*index);
// }

int	skip_non_arg(char *prompt_cmd, int *index)
{
	if (prompt_cmd[(*index) + 1] == prompt_cmd[*index])
		*index = *index + 1;
	(*index) = (*index) + 1;
	if ((prompt_cmd[*index] >= 9 && prompt_cmd[*index] <= 13)
		|| prompt_cmd[*index] == ' ')
		*index = *index + skip_white_spaces(&prompt_cmd[*index], 0);
	*index = *index + skip_io_redirection(&prompt_cmd[*index]);
	return (*index);
}

char	*reset_var(int *index)
{
	*index = 0;
	return (0);
}
