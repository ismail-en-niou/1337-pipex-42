/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:18:09 by ien-niou          #+#    #+#             */
/*   Updated: 2025/01/29 13:26:48 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	ft_delimeter(int i, char *str, char del)
{
	if (del == ' ')
		return (1);
	while (str[i])
	{
		if (str[i] == del)
			return (1);
		i++;
	}
	return (0);
}

char	*extract_token(int *i, char *str, char delimiter)
{
	int		start;
	int		len;
	char	*res;
	int		x;

	if (!ft_delimeter(*i, str, delimiter) || !str)
		return (NULL);
	start = (*i) + 1;
	len = 0;
	if (delimiter == ' ')
		x = 2;
	else
		x = 3;
	while (str[start] && str[start] != delimiter)
	{
		start++;
		len++;
	}
	res = malloc(len + x);
	ft_strlcpy(res, &str[*(i)], len + x);
	*i = start;
	return (res);
}

char	**ft_split_v2(char *str)
{
	int		count;
	char	**arr;
	int		i;
	int		j;

	count = ((j = 0), (i = 0), ft_tokens(str));
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (arr == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '"' || str[i] == '\'')
		{
			arr[j++] = extract_token(&i, str, str[i]);
			if (arr[j] == NULL)
				break ;
		}
		else
			arr[j++] = extract_token(&i, str, ' ');
	}
	return ((arr[j] = NULL), arr);
}
