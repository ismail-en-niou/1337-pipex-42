/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:17:43 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/10 20:38:30 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		fd;
	int		my_size;
	int		ac;
	char	**av;
}			t_cmd;

char		*ft_strjoin(char const *s1, char const *s2);
void		do_pipe(int *fd);
int			ft_open_file(char *file, int mode);
void		execute_command(t_cmd *cmd, char **env);
void		handle_pipex(char **av, char *env_path, int ac);
char		*ft_get_env(char **env);
void		*ft_free(char **res, int j);
char		*ft_find_cmd_path(char *cmd, char **paths);
size_t		take_size(char **s);
void		sefi_zemer(char **av);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlen(const char *src);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(const char *s1);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_travers(int i, const char *str, char delimiter);
int			ft_tokens(const char *str);
int			ft_delimeter(int i, char *str, char del);
char		*extract_token(int *i, char *str, char delimiter);
char		**ft_split_v2(char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_handler(char *av[], char *env[], int *fd);
#endif // PIPE_H