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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ft_travers(int i, const char *str, char delimiter) {
    i++;
    while (str[i] != delimiter && str[i] != '\0') {
        i++;
    }
    if (str[i] == delimiter)
        i++;
    return i;
}

int ft_tokens(const char *str) {
    int i = 0;
    int count = 0;
    int in_word = 0;

    while (str[i] != '\0') {
        if (str[i] == '"' || str[i] == '\'') {
            i = ft_travers(i, str, str[i]);
            count++;
            in_word = 0;
        } else if (str[i] == ' ') {
            if (in_word) {
                count++;
                in_word = 0;
            }
            i++;
        } else {
            in_word = 1;
            i++;
        }
    }
    if (in_word)
        count++;
    return count;
}

char *extract_token(int *i, const char *str, char delimiter) {
}

char **ft_split_v2(const char *str) {
    int count = ft_tokens(str);
    char **arr = (char **)malloc(sizeof(char *) * (count + 1));
    if (arr == NULL) {
        return NULL;
    }
    int i = 0, j = 0;
    while (str[i] != '\0') {
        while (str[i] == ' ') {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        if (str[i] == '"' || str[i] == '\'') 
            arr[j++] = extract_token(&i, str, str[i]);
        else
            arr[j++] = extract_token(&i, str, ' ');
    }
    arr[j] = NULL;
    return arr;
}


int main() {
    const char *str = "   Hello      \"this is a test\"   'and another'   world   ";
    char **res = ft_split_v2(str);
    for (int i = 0; res[i] != NULL; i++) {
        printf("%s\n", res[i]);
        free(res[i]);
    }
    free(res);
    return 0;
}
