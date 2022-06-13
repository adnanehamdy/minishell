/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/13 15:37:21 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(void)
{
	char	*prompt_cmd;

	while (1)
	{
		prompt_cmd = readline("\033[0;35mminishell> \033[0;37m");
		add_history(prompt_cmd);
		exit_code_handler(POSTEXIT, 0);
		parsing_functions(prompt_cmd);
	}
}