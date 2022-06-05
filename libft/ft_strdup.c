/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:09:52 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/06 11:27:24 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s1;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	while (s[i])
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}
