/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:22:23 by ien-niou          #+#    #+#             */
/*   Updated: 2025/01/28 12:07:56 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	i;

	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	dest_size = ft_strlen(dst);
	if (size <= dest_size)
		return (src_size + size);
	i = dest_size;
	while (*src && i + 1 < size)
		dst[i++] = *(src++);
	dst[i] = '\0';
	return (src_size + dest_size);
}
