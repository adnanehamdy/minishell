/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:46:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/07/02 23:21:01 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd_command(t_cmd_line *cmd)
{
	static char	*pwd;
	char		*temp;

	temp = pwd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = temp;
	else
		free(temp);
	ft_fprintf(cmd->out, "%s\n", pwd);
	return (0);
}
