/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:10:07 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/18 10:08:25 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src_bonus/pipe_bonus.h"

size_t	take_size(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	handle_child_process(t_cmd *cmds, int *fd, int i)
{
	if (i < cmds[0].my_size - 1)
		close(fd[0]);
	if (i == cmds[0].my_size - 1)
		childhandler(&cmds[i], cmds[i].env, cmds[i].fd_in, cmds[i].fd_out);
	else
		childhandler(&cmds[i], cmds[i].env, cmds[i].fd_in, fd[1]);
}

void	handle_cmds(t_cmd *cmds, int fd_in, int fd_out)
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
		cmds[i].fd_in = fd_prev;
		cmds[i].fd_out = fd_out;
		if (pids[i] == 0)
			handle_child_process(cmds, fd, i);
		if (fd_prev != fd_in)
			close(fd_prev);
		if (i < cmds[0].my_size - 1)
		{
			close(fd[1]);
			fd_prev = fd[0];
		}
	}
	wait_tt(-1, &pids, cmds[0].my_size, 1);
}

void	handle_pipex(char **av, char *env_path, int ac, char **env)
{
	char	**secure_path;
	int		i;
	t_cmd	*all_cmds;
	int		fd_in;
	int		fd_out;

	fd_in = ft_open_file(av[1], 0);
	fd_out = ft_open_file(av[ac - 1], 1);
	all_cmds = (t_cmd *)malloc(sizeof(t_cmd) * (ac - 3));
	if (!all_cmds)
		exit(1);
	secure_path = ((i = -1), ft_split(env_path, ':'));
	while (++i < ac - 3)
	{
		all_cmds[i].args = ft_split_v2(av[i + 2]);
		trim_quotes_and_spaces(all_cmds[i].args);
		all_cmds[i].path = ft_find_cmd_path(all_cmds[i].args[0], secure_path);
		all_cmds[i].my_size = ac - 3;
		all_cmds[i].env = ((all_cmds[i].ac = ac), env);
		all_cmds[i].av = ((all_cmds[i].index = i), av);
	}
	handle_cmds(all_cmds, fd_in, fd_out);
	ft_free(secure_path, take_size(secure_path));
	free_cmds(all_cmds, ac - 3);
	free(all_cmds);
}

int	main(int ac, char *av[], char *env[])
{
	char	*env_path;

	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdN outfile\n", 2);
		return (2);
	}
	env_path = ft_get_env(env);
	if (!env_path)
	{
		ft_putstr_fd("Error: PATH not found in environment\n", 2);
		return (3);
	}
	handle_pipex(av, env_path, ac, env);
	free(env_path);
	return (0);
}
