/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:10:24 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/15 11:22:52 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (dstsize <= len)
		return (ft_strlen(src) + dstsize);
	i = 0;
	j = len;
	while (src[i] && i < dstsize - (len + 1))
	{
		dst[j++] = src[i++];
	}
	dst[j] = 0;
	return (len + ft_strlen(src));
}
