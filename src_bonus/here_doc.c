/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:47:02 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/26 11:42:39 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

void	handle_cmds_here(t_cmd *cmds, int fd_in, int fd_out)
{
	pid_t	*pids;
	int		fd[2];
	int		fd_prev;
	int		i;

	fd_prev = ((pids = NULL), (i = -1), fd_in);
	wait_tt(-1, &pids, cmds[0].my_size, 0);
	while (++i < cmds[0].my_size)
	{
		if (i < cmds[0].my_size - 1 && do_pipe(fd) == -1)
			exit(1);
		pids[i] = do_fork();
		cmds[i].fd_in = ((cmds[i].fd_out = fd_out), fd_prev);
		if (pids[i] == 0)
			handle_child_process(cmds, fd, i);
		if (fd_prev != fd_in)
			close(fd_prev);
		if (i < cmds[0].my_size - 1)
			fd_prev = (close(fd[1]), fd[0]);
	}
	close(fd_in);
	close(fd_out);
	wait_tt(-1, &pids, cmds[0].my_size - 1, 1);
}

void	handle_pipex_here(char **av, char *env_path, int ac, char **env)
{
	char	**secure_path;
	int		i;
	t_cmd	*all_cmds;
	int		fd_in;
	int		fd_out;

	fd_in = ft_open_file(av[1], 0);
	fd_out = ft_open_file(av[ac - 1], 2);
	all_cmds = (t_cmd *)malloc(sizeof(t_cmd) * (ac - 4));
	if (!all_cmds)
		exit(1);
	secure_path = ((i = -1), ft_split(env_path, ':'));
	while (++i < ac - 4)
	{
		all_cmds[i].args = ft_split_v2(av[i + 3]);
		trim_quotes_and_spaces(all_cmds[i].args);
		all_cmds[i].path = ft_find_cmd_path(all_cmds[i].args[0], secure_path);
		all_cmds[i].my_size = ac - 4;
		all_cmds[i].env = ((all_cmds[i].ac = ac), env);
		all_cmds[i].av = ((all_cmds[i].index = i), av);
	}
	handle_cmds_here(all_cmds, fd_in, fd_out);
	ft_free(secure_path, take_size(secure_path));
	free_cmds(all_cmds, ac - 4);
	free(all_cmds);
}

static unsigned int	ft_simple_rand(void)
{
	unsigned int	seed;
	int				fd;

	seed = 0;
	if (seed == 0)
	{
		fd = open("/dev/urandom", O_RDONLY);
		if (fd == -1 || read(fd, &seed, sizeof(seed)) != sizeof(seed))
			seed = 42;
		close(fd);
	}
	seed = (seed * 99 + 123456799) % 456789;
	return (seed);
}

char	*ft_rand(void)
{
	return (ft_itoa(ft_simple_rand()));
}

void	handel_herdoc(char **av, char *env_path, int ac, char **env)
{
	char	*here_doc;
	int		fd;
	char	*rand;
	char	*line;

	here_doc = ((rand = ft_rand()), ft_strjoin(rand, ".txt"));
	free(rand);
	av[1] = ft_strjoin("/tmp/", here_doc);
	free(here_doc);
	fd = ft_open_file(av[1], 1);
	write(0, "=> ", 4);
	line = get_next_line(0);
	while (line)
	{
		write(fd, line, ft_strlen(line));
		if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
			&& line[ft_strlen(av[2])] == '\n')
			break ;
		free(line);
		write(2, "=> ", 4);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
	handle_pipex_here(av, env_path, ac, env);
}
