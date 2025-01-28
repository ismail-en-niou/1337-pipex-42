/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:34:21 by ien-niou          #+#    #+#             */
/*   Updated: 2025/01/28 20:02:32 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	*ft_free(char **res, int j)
{
	while (j > 0)
		free(res[--j]);
	free(res);
	return (NULL);
}

static char	*ft_strcpy_w(char const *src, char sep)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	i = 0;
	while (src[len] && src[len] != sep)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (free(word), NULL);
	while (i < len)
	{
		word[i] = src[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	count_word(char const *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;
	int		count;

	i = 0 ;
	j = 0 ;
	count = count_word(s,c);
	if (!count)
		return (NULL);
	res = malloc((count + 1) * sizeof(char *));
	if (!s || !(res))
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			res[j] = ft_strcpy_w(&s[i], c);
			if (!res[j++])
				return (ft_free(res, j - 1));
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (res[j] = NULL, res);
}