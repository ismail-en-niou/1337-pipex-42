/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ien-niou <ien-niou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:18:09 by ien-niou          #+#    #+#             */
/*   Updated: 2025/01/28 20:33:56 by ien-niou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int ft_travers(int i , char *str , char s) {
    i++; 
    while (str[i] != s && str[i] != '\0') {
        i++;
    }
    if (str[i] == s) {
        i++;
    }
    return i;
}

int ft_tokens(char *str) {
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (str[i] == '"' || str[i] == '\'') {
            i = ft_travers(i, str, str[i]);
            count++;
        } else if (str[i] == ' ') {
            i = ft_travers(i, str, ' ');
            count++;
        } else {
            i++;
        }
    }
    return count;
}

void ft_split_v2(char *str)
{
    int count;

    count = ft_tokens(str);
    printf("%d",count);
}

int main()
{
    char *str ;

    str = "Hello \"this is a test\" 'and another' world"; 
    ft_split_v2(str);
    return 0;
}
