/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:44:53 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/25 15:49:18 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

static int	ft_nb_len(int n)
{
	int		i;
	long	x;

	x = n;
	i = 1;
	if (x < 0)
	{
		i++;
		x *= -1;
	}
	while (x > 9)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

static void	ft_allocation(char *res, int len, long n, int sign)
{
	res[len] = '\0';
	len--;
	if (n == 0)
		res[len] = '0';
	if (sign)
		res[0] = '-';
	while (n)
	{
		res[len] = (n % 10) + '0';
		len--;
		n /= 10;
	}
}

char	*ft_itoa(unsigned int x)
{
	int		len;
	char	*res;
	int		sign;
	long	n;

	n = x;
	len = ft_nb_len(n);
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_allocation(res, len, n, sign);
	return (res);
}
