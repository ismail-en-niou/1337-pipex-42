/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:01 by ien-niou          #+#    #+#             */
/*   Updated: 2025/01/29 13:27:18 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	ft_travers(int i, const char *str, char delimiter)
{
	i++;
	while (str[i] != delimiter && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == delimiter)
		i++;
	return (i);
}

int	ft_tokens(const char *str)
{
	int	i;
	int	count;
	int	in_word;

	in_word = (((i = 0), count = 0), 0);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = ft_travers(i, str, str[i]);
			count++;
			in_word = 0;
		}
		else if (str[i] == ' ')
		{
			if (in_word)
				in_word = ((count++), 0);
			i++;
		}
		else
			in_word = ((i++), 1);
	}
	if (in_word)
		count++;
	return (count);
}
