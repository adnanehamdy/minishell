/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:45:38 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/22 23:59:02 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_putnbr_base_unsigned(int fd, unsigned int nbr, char *base)
{
	size_t	rt;
	size_t	b;

	b = ft_strlen(base);
	rt = 0;
	if (nbr >= b)
	{
		rt += ft_putnbr_base_unsigned(fd, (nbr / b), base);
		return (ft_fputchar(fd, base[(nbr % b)]) + rt);
	}
	else
		return (ft_fputchar(fd, base[nbr]));
}

int	ft_putnbr_base(int fd, int nbr, char *base)
{
	unsigned int	nbr_p;
	size_t			rt;
	size_t			b;

	nbr_p = (unsigned int)nbr;
	b = ft_strlen(base);
	rt = 0;
	if (nbr < 0)
	{
		if (!ft_strncmp(base, DECB, b))
		{
			nbr_p = nbr * (-1);
			rt += ft_fputchar(fd, '-');
		}
		if (nbr_p >= b)
			rt += ft_putnbr_base(fd, (nbr_p / b), base);
		return (ft_fputchar(fd, base[nbr_p % b]) + rt);
	}
	else if (nbr_p >= b)
	{
		rt += ft_putnbr_base(fd, (nbr_p / b), base);
		return (ft_fputchar(fd, base[(nbr_p % b)]) + rt);
	}
	else
		return (ft_fputchar(fd, base[nbr_p]));
}

int	ft_putnbr_address(int fd, unsigned long long nbr, char *base)
{
	size_t	rt;
	size_t	b;

	b = ft_strlen(base);
	rt = 0;
	if (nbr >= b)
	{
		rt += ft_putnbr_address(fd, (nbr / b), base);
		return (ft_fputchar(fd, base[(nbr % b)]) + rt);
	}
	else
		return (ft_fputchar(fd, base[nbr]));
}

int	ft_print_address(int fd, void *str)
{
	int	sw;

	sw = ft_fputstr(fd, "0x");
	return (ft_putnbr_address(fd, (long long)str, LHEXB) + sw);
}
