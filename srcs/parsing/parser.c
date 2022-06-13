/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/13 15:50:48 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_data(char *prompt_cmd)
{
	int	cmd_number;

	cmd_number = count_cmd_number(prompt_cmd);
	initialize_cmd_line(prompt_cmd, cmd_number);
}
	
void	parsing_functions(char *prompt_cmd)
{
	if (prompt_cmd)
		error_checker(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 1) && prompt_cmd[0])
		parse_data(prompt_cmd);
	else
		printf("exit code = %d\n", exit_code_handler(GETEXIT, 1));
}
