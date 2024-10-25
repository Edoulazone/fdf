/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:24:17 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/15 15:01:24 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_all(char **c)
{
	int	i;

	i = 0;
	while (c[i] != NULL)
	{
		free(c[i]);
		i++;
	}
	return (NULL);
}

static int	number_words(char const *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index])
	{
		while (s[index] == c && s[index])
			index++;
		if (s[index] != '\0')
			count++;
		while (s[index] != c && s[index])
			index++;
	}
	return (count);
}

static char	*word_length(char const *s, char c)
{
	char	*new;
	int		i;
	int		index;
	int		len_word;

	i = 0;
	index = 0;
	len_word = 0;
	while (s[index] != c && s[index])
	{
		index++;
		len_word++;
	}
	new = (char *)malloc((len_word + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < len_word)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	**make_tab(const char *s, char c, int nbr_words, char **news_s)
{
	int	i;
	int	index;

	i = -1;
	index = 0;
	while (s[index] && i < nbr_words)
	{
		while (s[index] == c && s[index])
			index++;
		if (s[index] != '\0')
		{
			news_s[++i] = word_length(&s[index], c);
			if (news_s[i] == NULL)
				return (free_all(news_s), free(news_s), NULL);
		}
		while (s[index] != c && s[index])
			index++;
	}
	return (news_s);
}

char	**ft_split(char const *s, char c)
{
	int		nbr_words;
	char	**news_s;

	if (!s)
		return (NULL);
	nbr_words = number_words(s, c) + 1;
	news_s = (char **)malloc((nbr_words) * sizeof(char *));
	if (!news_s)
		return (NULL);
	if (make_tab(s, c, nbr_words, news_s) == NULL)
		return (NULL);
	news_s[nbr_words - 1] = NULL;
	return (news_s);
}
