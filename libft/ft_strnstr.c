/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:33:15 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/06 15:34:41 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndle, size_t len)
{
	unsigned char	*h;
	size_t			i;

	h = (unsigned char *)hay;
	i = 0;
	if (*ndle == 0)
		return ((char *)h);
	else
	{
		while (*h && i < len)
		{
			if (len - i++ < ft_strlen(ndle))
				return (0);
			if (!(ft_strncmp((char *)h, ndle, ft_strlen(ndle))))
			{
				return ((char *)h);
			}
			h++;
		}
	}
	return (0);
}
