/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:04:22 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:55:03 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*skip_delimiters(char *str, char delimiter)
{
	while (*str == delimiter)
		str++;
	return (str);
}

int	get_word_length(char *str, char delimiter)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != delimiter)
		len++;
	return (len);
}

char	*allocate_and_copy_word(char *str, int len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strncpy_fdf(word, str, len);
	word[len] = '\0';
	return (word);
}

int	fill_split_array(char **result, char *str, char delimiter, int count)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	while (*str && i < count)
	{
		str = skip_delimiters(str, delimiter);
		len = get_word_length(str, delimiter);
		word = allocate_and_copy_word(str, len);
		if (!word)
		{
			free_split(result);
			return (0);
		}
		result[i] = word;
		str += len;
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**split_line(char *str, char delimiter)
{
	char	**result;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str, delimiter);
	result = allocate_split_array(word_count);
	if (!result)
		return (NULL);
	if (!fill_split_array(result, str, delimiter, word_count))
		return (NULL);
	return (result);
}
