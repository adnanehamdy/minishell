/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:46:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/23 01:09:49 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	pwd_command(t_cmd_line *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_fprintf(cmd->out, "%s\n", pwd);
	free(pwd);
	return (0);
}

// int main(void)
// {
// 	pwd_command();
// 	return (0);
// }