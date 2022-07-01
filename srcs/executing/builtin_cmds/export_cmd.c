/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:21:20 by nelidris          #+#    #+#             */
/*   Updated: 2022/07/01 08:21:13 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_env_var(char *var, int *err_occ, char **envp)
{
	 
}

int	export_command(t_cmd_line *cmd)
{
	int err_occ;
	int	i;

	err_occ = 0;
	i = 1;
	while (cmd->command[i])
		set_env_var(cmd->command[i], &err_occ,
			envp_handler(GETENV, NULL));
		
	return (0);
}