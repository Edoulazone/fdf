/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:40:31 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/15 14:40:36 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char) c)
		{
			return ((char *) str);
		}
		str++;
	}
	if (!*str && (char)c == '\0')
	{
		return ((char *) str);
	}
	return (NULL);
}
