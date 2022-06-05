/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:59:17 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/12 15:14:30 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	i;

	if (!s1 || !set)
		return (0);
	size = ft_strlen(s1);
	i = 0;
	size--;
	while (size >= 0 && ft_strchr(set, s1[size]))
		size--;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (ft_substr(s1, i, size - i + 1));
}
