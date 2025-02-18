/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:18:09 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/17 09:17:13 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

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

	if (!str)
		return (NULL);
	start = *i;
	len = 0;
	if (str[start] == '"' || str[start] == '\'')
		start++;
	while (str[start + len] && str[start + len] != delimiter)
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, &str[start], len + 1);
	if (str[start + len] == delimiter)
		*i = start + len + 1;
	else
		*i = start + len;
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
	if (!arr)
		return (NULL);
	while (str[i] != '\0' && j < count)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '"' || str[i] == '\'')
			arr[j] = extract_token(&i, str, str[i]);
		else
			arr[j] = extract_token(&i, str, ' ');
		if (!arr[j])
			return (free_splitv2(arr, j - 1), NULL);
		j++;
	}
	arr[j] = NULL;
	return (arr);
}
