/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:44:32 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/22 15:56:46 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	while (s1[i])
	{
		if ((char)c == s1[i])
			return (&s1[i]);
		i++;
	}
	if (s1[i] == (char)c)
		return (&s1[i]);
	return (NULL);
}
