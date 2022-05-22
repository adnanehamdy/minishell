/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/22 14:29:56 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_data(char *prompt_cmd)
{
	int	cmd_number;
	int	i;
	char **cmd;

	i = 0;
	cmd_number = 0;
	cmd_number = count_cmd_number(prompt_cmd);
	count_each_arg(NULL, 0, 1);
	fill_each_arg(NULL, NULL, 0, 1);
	while (i++ < cmd_number)
	{
		cmd = initialize_cmd_line(prompt_cmd, cmd_number);
		printf("%d\n", i);
	}
	// while (cmd[i])
	// 	printf("%s\n", cmd[i++]);
 	// while (i < count_arg_number(prompt_cmd))
	// {
	// 	cmd_number = count_each_arg(prompt_cmd, 0);
	// 	i++;
	// }
}

void	parsing_functions(char *prompt_cmd)
{
	error_checker(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 1))
		parse_data(prompt_cmd);
	else
		printf("exit code = %d\n", exit_code_handler(GETEXIT, 1));
}
