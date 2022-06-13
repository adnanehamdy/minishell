/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:57:35 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 14:54:34 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// int	exit_code_handler(int mod, int value)
// {
// 	static int exit_code;
	
// 	if (mod == GETEXIT)
// 		return exit_code;
// 	else if (mod == POSTEXIT)
// 		exit_code = value;
// 	return (0);
// }

void	exit_command( void )
{
	exit(exit_code_handler(GETEXIT, 0));
}

// int main(void)
// {
// 	exit_command();
// 	return (0);
// }