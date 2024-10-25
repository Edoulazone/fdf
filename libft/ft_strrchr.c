/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:13:55 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 17:14:04 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*buffer;
	int		i;

	buffer = NULL;
	i = ft_strlen(str);
	if (!*(str + i) && (char)c == '\0')
	{
		return ((char *)str + i);
	}
	while (*str)
	{
		if (*str == (char) c)
			buffer = ((char *) str);
		str++;
	}
	if (buffer)
		return ((char *) buffer);
	return (NULL);
}