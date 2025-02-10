/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:59:56 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/10 20:41:53 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char    *ft_get_env(char **env)
{
    int    i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (ft_strdup(env[i] + 5));
        i++;
    }
    return (NULL);
}

char    *ft_find_cmd_path(char *cmd, char **paths)
{
    int        i;
    char    *full_path;
    char    *tmp;

    if (!cmd)
        return (NULL);
    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    if (!paths || !*paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

void    sefi_zemer(char **av)
{
    int    i;

    i = 0;
    while (av[i])
    {
        av[i] = ft_strtrim(av[i], "'");
        av[i] = ft_strtrim(av[i], "\"");
        if (av[i] && av[i][0] == ' ')
        {
            free(av[i]);
            av[i] = NULL;
            break ;
        }
        i++;
    }
}

int    ft_open_file(char *file, int mode)
{
    int    fd;

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

pid_t    do_fork(void)
{
    pid_t    pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork fail");
        exit(1);
    }
    return (pid);
}

void    execute_command(t_cmd *cmd, char **env)
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

void    __childHandler(int i, t_cmd *cmds, char **env, int fd_prev[2], int fd_next[2])
{
    if (i == 0)
    {
        dup2(cmds[i].fd, STDIN_FILENO);
        dup2(fd_next[1], STDOUT_FILENO);
        close(cmds[i].fd);
        close(fd_next[0]);
        close(fd_next[1]);
    }
    else if (i == cmds[i].my_size - 1)
    {
        dup2(fd_prev[0], STDIN_FILENO);
        dup2(cmds[i].fd, STDOUT_FILENO);
        close(cmds[i].fd);
        close(fd_prev[0]);
        close(fd_prev[1]);
    }
    else
    {
        dup2(fd_prev[0], STDIN_FILENO);
        dup2(fd_next[1], STDOUT_FILENO);
        close(fd_prev[0]);
        close(fd_prev[1]);
        close(fd_next[0]);
        close(fd_next[1]);
    }
    execute_command(&cmds[i], env);
}

void    _handleCmds(t_cmd *cmds, char **env)
{
    pid_t    *pid;
    int        fd_prev[2] = {-1, -1};
    int        fd_next[2] = {-1, -1};
    int        i;
    int        status;

    pid = malloc(sizeof(pid_t) * cmds[0].my_size);
    if (!pid)
        exit(1);
    i = 0;
    while (i < cmds[0].my_size)
    {
        if (i < cmds[0].my_size - 1)
        {
            if (pipe(fd_next) == -1)
            {
                perror("pipe error");
                exit(1);
            }
        }
        pid[i] = do_fork();
        if (pid[i] == 0)
            __childHandler(i, cmds, env, fd_prev, fd_next);
        if (fd_prev[0] != -1)
        {
            close(fd_prev[0]);
            close(fd_prev[1]);
        }
        fd_prev[0] = fd_next[0];
        fd_prev[1] = fd_next[1];
        i++;
    }
    if (fd_prev[0] != -1)
    {
        close(fd_prev[0]);
        close(fd_prev[1]);
    }
    i = -1;
    while (++i < cmds[0].my_size)
        waitpid(pid[i], &status, 0);
    free(pid);
}

size_t		take_size(char **s)
{
	int i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void    handel_pipex(char **av, char *_env, int ac)
{
    int        i;
    char    **secure_path;
    t_cmd    *all_cmds;

    secure_path = ft_split(_env, ':');
    all_cmds = malloc(sizeof(t_cmd) * (ac - 3));
    if (!all_cmds)
        exit(1);
    i = 0;
    while (i < ac - 3)
    {
        all_cmds[i].args = ft_split_v2(av[i + 2]);
        sefi_zemer(all_cmds[i].args);
        all_cmds[i].fd = -1;
        all_cmds[i].path = ft_find_cmd_path(all_cmds[i].args[0], secure_path);
        all_cmds[i].my_size = ac - 3;
        all_cmds[i].ac = ac;
        all_cmds[i].av = av;
        i++;
    }
    all_cmds[0].fd = ft_open_file(av[1], 0);
    all_cmds[i - 1].fd = ft_open_file(av[ac - 1], 1);
    _handleCmds(all_cmds, secure_path);
    free(all_cmds);
    ft_free(secure_path,take_size(secure_path));
}

int    main(int ac, char *av[], char *env[])
{
    char    *Env;

    if (ac < 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdN outfile\n", 2);
        return (2);
    }
    Env = ft_get_env(env);
    if (!Env)
    {
        ft_putstr_fd("Error: PATH not found in environment\n", 2);
        return (3);
    }
    handel_pipex(av, Env, ac);
    free(Env);
    return (0);
}