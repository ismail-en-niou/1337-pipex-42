/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:05:01 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/18 09:14:30 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

pid_t	do_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork fail");
		exit(1);
	}
	return (pid);
}

void	execute_command(t_cmd *cmd, char **env)
{
	if (!cmd->path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execve(cmd->path, cmd->args, env);
	perror("execve");
	exit(1);
}

void	childhandler(t_cmd *cmds, char **env, int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	execute_command(cmds, env);
	exit(1);
}

int	do_pipe(int *fd)
{
	int	i;

	i = pipe(fd);
	if (i == -1)
	{
		perror("pipe error");
		exit(1);
	}
	return (i);
}

void	free_cmds(t_cmd *cmds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (cmds[i].args)
			ft_free(cmds[i].args, take_size(cmds[i].args));
		if (cmds[i].path)
			free(cmds[i].path);
		i++;
	}
}
