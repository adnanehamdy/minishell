/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:21:20 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 14:53:57 by ahamdy           ###   ########.fr       */
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
	return (err_occ);
}
