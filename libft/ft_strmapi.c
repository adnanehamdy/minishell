/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:13:08 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/12 11:47:45 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	char	*s1;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (0);
	size = ft_strlen(s);
	s1 = (char *)malloc(size + 1);
	if (!s1)
		return (0);
	while (s[i])
	{
		s1[i] = f(i, s[i]);
		i++;
	}
	s1[i] = 0;
	return (s1);
}
