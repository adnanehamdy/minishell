/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:00:03 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/11 19:58:55 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	store(const char *str, int sign)
{
	size_t	res;

	res = 0;
	while (ft_isdigit(*str) && *str)
	{
		if ((unsigned long)(res * 10 + (*str - '0'))
		> 9223372036854775807 && sign == 1)
			return (-1);
		else if ((unsigned long)(res * 10 + (*str - '0'))
		> (unsigned long)9223372036854775807 + 1 && sign == -1)
			return (0);
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (sign * (long)res);
}

int	ft_atoi(const char *str)
{
	size_t	sign;
	size_t	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (store(str, sign));
}
