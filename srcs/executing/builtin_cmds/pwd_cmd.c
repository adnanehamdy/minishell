/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:46:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/16 19:14:01 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	pwd_command(t_cmd_line *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STANDARD_OUTPUT);
	free(pwd);
	return (0);
}

// int main(void)
// {
// 	pwd_command();
// 	return (0);
// }