/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:29:25 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/23 00:26:09 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fputchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_fputstr(int fd, char *str)
{
	size_t	i;

	if (!str)
		return (write(fd, "(null)", 6));
	i = ft_strlen(str);
	return (write(fd, str, i));
}
