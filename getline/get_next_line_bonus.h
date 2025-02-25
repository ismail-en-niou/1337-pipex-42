/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:45:36 by ien-niou          #+#    #+#             */
/*   Updated: 2025/02/25 15:51:12 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strdup_get(char *s);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_substr_get(char *s, unsigned int start, size_t len);
char	*ft_strchr_get(const char *s, int c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif