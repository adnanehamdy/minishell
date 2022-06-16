/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:12:43 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/13 14:55:08 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ptrlen(char	**pstr)
{
	size_t len;

	len = 0;
	while (pstr[len])
		len++;
	return (len);
}