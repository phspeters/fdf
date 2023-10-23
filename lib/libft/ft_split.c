/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:39:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/12 12:33:59 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(const char *str, const char delimiter)
{
	int	len;

	len = 0;
	while ((str[len] != delimiter) && (str[len] != '\0'))
		len++;
	return (len);
}

static void	*free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_count;
	int		array_index;
	int		len;

	array_index = 0;
	word_count = ft_count_words(s, c);
	split = malloc(sizeof(char *) * (word_count + 1));
	while ((array_index < word_count) && split != NULL)
	{
		while (*s == c)
			s++;
		split[array_index] = malloc(sizeof(char) * (wordlen(s, c) + 1));
		if (split[array_index] == NULL)
			return (free_split(split));
		len = 0;
		while ((*s != c) && (*s != '\0'))
			split[array_index][len++] = *s++;
		split[array_index++][len] = '\0';
	}
	if (split != NULL)
		split[array_index] = NULL;
	return (split);
}
