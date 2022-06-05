/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:40:34 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/12 12:28:03 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*s;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc(i + 1);
	i = 0;
	if (!s)
		return (0);
	while (s1[j])
		s[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = 0;
	return (s);
}
