/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:11 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 20:22:06 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_putstr(char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	len = 0;
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	len += ft_putchar((nb % 10) + '0');
	return (len);
}

int	get_precision(const char *format, int *i)
{
	int	precision;

	precision = 6;
	if (format[*i] == '.')
	{
		(*i)++;
		precision = 0;
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			precision = precision * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	return (precision);
}

int	ft_put_decimal_part(double decimal_part, int precision)
{
	int	len;
	int	i;

	len = 0;
	if (precision > 0)
	{
		len += ft_putchar('.');
		i = 0;
		while (i < precision)
		{
			decimal_part *= 10;
			len += ft_putchar((int)decimal_part + '0');
			decimal_part -= (int)decimal_part;
			i++;
		}
	}
	return (len);
}

int	ft_putfloat(double n, int precision)
{
	int		len;
	long	integer_part;
	double	decimal_part;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		n = -n;
	}
	integer_part = (long)n;
	decimal_part = n - integer_part;
	len += ft_putnbr(integer_part);
	len += ft_put_decimal_part(decimal_part, precision);
	return (len);
}
