/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:08:15 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/17 10:11:01 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unset_friendly(char *var)
{
	size_t	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	if (ft_strchr(var, '='))
		return (0);
	i = 0;
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
