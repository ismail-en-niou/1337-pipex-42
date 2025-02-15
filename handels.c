/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handels.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:01:30 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/15 12:03:13 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*ft_get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	*ft_find_cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	if (!paths || !*paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	trim_quotes_and_spaces(char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		av[i] = ft_strtrim(av[i], "'\"");
		if (av[i] && av[i][0] == ' ')
		{
			free(av[i]);
			av[i] = NULL;
			break ;
		}
		i++;
	}
}

int	ft_open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}
