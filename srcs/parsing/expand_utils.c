/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:19:32 by ahamdy            #+#    #+#             */
/*   Updated: 2022/06/30 12:29:03 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i + 1] && s1[i + 1] != '=')
		i++;
	if (ft_strlen(s2) != i + 1)
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
