/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:27:02 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/25 06:07:03 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_cmd_args(char **cmd_path)
{
	size_t	i;

	i = 0;
	while (cmd_path[i])
		free(cmd_path[i++]);
	free(cmd_path);
}

void	free_cmd_line(t_cmd_line **cmd_line)
{
	size_t	i;

	i = 0;
	while (cmd_line[i])
	{
		free(cmd_line[i]->cmd_path);
		free_cmd_args(cmd_line[i]->command);
		free(cmd_line[i]);
		i++;
	}
	free(cmd_line);
}