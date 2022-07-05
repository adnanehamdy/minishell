/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:37:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/25 22:27:54 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static t_cmd_line	**parse_data(char *prompt_cmd)
{
	int	cmd_number;
	
	cmd_number = count_cmd_number(prompt_cmd);
	return (initialize_cmd_line(prompt_cmd, cmd_number));
}
	
t_cmd_line	**parsing_functions(char *prompt_cmd)
{
	int exit_status;

	if (!prompt_cmd)
		return (0);
	exit_status = error_checker(prompt_cmd);
	if (!exit_code_handler(GETEXIT, 0) && prompt_cmd[0])
	{
		exit_code_handler(POSTEXIT, exit_status);
		return (parse_data(prompt_cmd));
	}
	return (0);
}
