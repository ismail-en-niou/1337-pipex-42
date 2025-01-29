/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:31:55 by ien-niou          #+#    #+#             */
/*   Updated: 2025/01/29 13:28:01 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*get_env(char **env)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			res = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	return (res);
}

void	handeler(char **av, char **env)
{
	int		fd[2];
	int		i;
	char	*test;
	char	**cmd1;
	int		pid1;

	i = 0;
	if (pipe(fd) == -1)
		perror("error : ");
	cmd1 = ft_split_v2(av[1]);
	if (!cmd1)
		return (free(cmd1));
	pid1 = fork();
	if (pid1 < 0)
		return ;
	if (pid1 == 0)
	{
		while (env[i])
		{
			test = ft_strjoin(env[i], "/");
			test = ft_strjoin(test, cmd1[0]);
			execve(test, cmd1, NULL);
			free(test);
			i++;
		}
	}
	else
	{
		// hada P
	}
	waitpid(pid1, NULL, 0);
}

int	main(int ac, char *av[], char *env[])
{
	char *str = get_env(env);
	char **res;
	res = ft_split(str, ':');
	int i = 0;
	handeler(av, res);

	return (0);
}