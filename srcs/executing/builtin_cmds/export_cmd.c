/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:21:20 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/05 17:52:21 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export_command(t_cmd_line *cmd)
{
	int	err_occ;
	int	i;

	if (!cmd->command[1])
		display_exported_vars(cmd, envp_handler(GETENV, NULL));
	err_occ = 0;
	i = 1;
	while (cmd->command[i])
		set_env_var(cmd->command[i++], &err_occ,
			envp_handler(GETENV, NULL));
	return (0);
}
