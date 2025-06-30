/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:35:16 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 20:21:07 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_puthex(unsigned long n, char format)
{
	int		len;
	char	*base;

	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
		len += ft_puthex(n / 16, format);
	len += ft_putchar(base[n % 16]);
	return (len);
}

int	ft_putptr(void *ptr)
{
	int				len;
	unsigned long	addr;

	if (!ptr)
		return (ft_putstr("(nil)"));
	addr = (unsigned long)ptr;
	len = ft_putstr("0x");
	len += ft_puthex(addr, 'x');
	return (len);
}

int	ft_handle_basic_formats(char specifier, va_list args)
{
	int	len;

	len = 0;
	if (specifier == 'c')
		len = ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		len = ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		len = ft_putunsigned(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		len = ft_puthex(va_arg(args, unsigned int), specifier);
	else if (specifier == 'p')
		len = ft_putptr(va_arg(args, void *));
	else if (specifier == '%')
		len = ft_putchar('%');
	else
		len = ft_putchar(specifier);
	return (len);
}

int	ft_handle_format(const char *format, int *i, va_list args)
{
	int		len;
	int		precision;
	char	specifier;

	len = 0;
	precision = get_precision(format, i);
	specifier = format[*i];
	if (specifier == 'f')
		len = ft_putfloat(va_arg(args, double), precision);
	else
		len = ft_handle_basic_formats(specifier, args);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			len += ft_handle_format(format, &i, args);
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
