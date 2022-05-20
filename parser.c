/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/19 13:04:00 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_data(char *prompt_cmd)
{
	int	cmd_number;

	cmd_number = 0;
 	// initialize_cmd_line(prompt_cmd, cmd_number);
	cmd_number = count_each_arg(prompt_cmd);
	printf("%d\n", cmd_number);
}

void	parsing_functions(char *prompt_cmd)
{
	error_checker(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 1))
		parse_data(prompt_cmd);
	else
		printf("exit code = %d\n", exit_code_handler(GETEXIT, 1));
}
