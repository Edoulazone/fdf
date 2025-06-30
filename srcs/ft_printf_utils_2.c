/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:17:23 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 20:22:12 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_putunsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_putunsigned(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
