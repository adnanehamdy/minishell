/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:31:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/08/06 15:05:10 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	ft_write_sign(int fd, char id, va_list arg)
{
	if (id == 'c')
		return (ft_fputchar(fd, va_arg(arg, int)));
	if (id == 's')
		return (ft_fputstr(fd, va_arg(arg, char *)));
	if (id == 'p')
		return (ft_print_address(fd, va_arg(arg, void *)));
	if (id == 'd' || id == 'i')
		return (ft_putnbr_base(fd, va_arg(arg, int), DECB));
	if (id == 'u')
		return (ft_putnbr_base_unsigned(fd, (va_arg(arg, unsigned int)), DECB));
	if (id == 'x')
		return (ft_putnbr_base(fd, va_arg(arg, int), LHEXB));
	if (id == 'X')
		return (ft_putnbr_base(fd, va_arg(arg, int), UHEXB));
	if (id == '%')
		return (write(fd, &id, 1));
	return (0);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	arg;
	size_t	i;
	int		suwr;

	va_start(arg, str);
	i = 0;
	suwr = 0;
	while (str[i])
	{
		if (str[i] == '%')
			suwr += ft_write_sign(fd, str[++i], arg);
		else
			suwr += write(fd, &str[i], 1);
		i++;
	}
	va_end(arg);
	return (suwr);
}
