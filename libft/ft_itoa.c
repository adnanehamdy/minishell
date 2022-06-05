/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:56:31 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/12 14:21:05 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int c)
{
	size_t	count;

	count = 0;
	if (c < 0)
	{
		count = 1;
		c *= -1;
	}
	while (c > 0)
	{
		c /= 10;
		count++;
	}
	return (count);
}

static char	*ft_convert(char *num, int n, int count)
{
	if (n < 0)
	{
		num[0] = '-';
		ft_convert(num, n * -1, count--);
	}
	else if (n >= 10)
	{
		num[count--] = n % 10 + 48;
		ft_convert(num, n / 10, count);
	}
	else
		num[count] = n + 48;
	return (num);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*num;

	num = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
	{
		num = (char *)malloc(2);
		num[0] = '0';
		num[1] = 0;
		return (num);
	}
	count = (int)ft_count(n);
	num = (char *)malloc(count + 1);
	if (!num)
		return (0);
	num[count] = '\0';
	return (ft_convert(num, n, --count));
}

/*#include<stdio.h>

int	main(void)
{
	int	c;

	c = -2147483648LL;
	//c = -83648;
	printf("%s", ft_itoa(c));
}*/
