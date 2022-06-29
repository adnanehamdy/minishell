/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:35:11 by nelidris          #+#    #+#             */
/*   Updated: 2022/06/22 23:58:54 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# define DECB "0123456789"
# define UHEXB "0123456789ABCDEF"
# define LHEXB "0123456789abcdef"

int		ft_fprintf(int fd, const char *str, ...);
char	*ft_itoa_base(int nbr, char *base);
int		ft_fputstr(int fd, char *str);
int		ft_fputchar(int fd, char c);
int		ft_print_address(int fd, void *str);
int		ft_putnbr_base_unsigned(int fd, unsigned int nbr, char *base);
int		ft_putnbr_base(int fd, int nbr, char *base);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif