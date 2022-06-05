/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:40:50 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/12 12:28:28 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		count = 1;
	else if (ft_strlen(s) > (len + start))
		count = len + 1;
	else if (ft_strlen(s) <= (len + start))
		count = ft_strlen(s) - (start) + 1;
	c = (char *)malloc(count);
	if (!c)
		return (0);
	while (count > 1 && len-- && s[start])
		c[i++] = s[start++];
	c[i] = 0;
	return (c);
}
