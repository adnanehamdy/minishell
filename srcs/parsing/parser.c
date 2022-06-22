/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/22 02:03:48 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static t_cmd_line	**parse_data(char *prompt_cmd)
{
	int	cmd_number;
	
	cmd_number = count_cmd_number(prompt_cmd);
	return (initialize_cmd_line(prompt_cmd, cmd_number));
}
	
t_cmd_line	**parsing_functions(char *prompt_cmd)
{
	if (!prompt_cmd)
		return (0);
	error_checker(prompt_cmd);
	/* error handling need to be fixed, when an error is occured, no more command can execute.
		edit: fixed ! */
	if (!exit_code_handler(GETEXIT, 0) && prompt_cmd[0])
		return (parse_data(prompt_cmd));
	return (0);
}
