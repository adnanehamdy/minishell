/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:10:16 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/18 08:24:41 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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