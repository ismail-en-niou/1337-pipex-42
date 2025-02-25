/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:52 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/24 20:27:19 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char **storage)
{
	char	*line;
	char	*newline_ptr;
	char	*temp;

	newline_ptr = ft_strchr_get(*storage, '\n');
	if (newline_ptr)
	{
		line = ft_substr_get(*storage, 0, newline_ptr - *storage + 1);
		temp = ft_strdup_get(newline_ptr + 1);
		free(*storage);
		*storage = temp;
	}
	else
	{
		line = ft_strdup_get(*storage);
		free(*storage);
		*storage = NULL;
	}
	return (line);
}

static int	read_to_storage(int fd, char **storage)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(*storage);
		*storage = NULL;
		return (-1);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin_get(*storage, buffer);
		free(*storage);
		*storage = temp;
		if (ft_strchr_get(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_to_storage(fd, &storage);
	if (bytes_read < 0 || (!storage && bytes_read == 0))
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = extract_line(&storage);
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
