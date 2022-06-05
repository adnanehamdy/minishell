/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:31:17 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/12 12:28:19 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*s1;

	s1 = (char *)s;
	i = ft_strlen(s1);
	while (i)
	{
		if (s1[i] == (char)c)
			return (&s1[i]);
		i--;
	}
	if (s1[i] == (char)c)
		return (&s1[i]);
	return (NULL);
}
