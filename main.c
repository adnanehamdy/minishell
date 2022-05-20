/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:41:02 by ahamdy            #+#    #+#             */
/*   Updated: 2022/05/18 08:19:30 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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