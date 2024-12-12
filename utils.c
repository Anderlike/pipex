/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:41:38 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/12/12 15:41:38 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/pipex.h"

void ft_free(char **target)
{
    size_t i;

    i = 0;
    while(target[i])
    {
        free(target[i]);
        i++;
    }
    free(target);
}

int open_file(char *file, int read)
{
    int res;

    if(read == 0)
        res = open(file, O_RDONLY, 0777);
    else if(read == 1)
        res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else
        exit(0);
    return res;
}

char *get_env(char *cmd, char **env)
{
    int i;
    int j;
    char *sub;

    i = 0;
    while(env[i])
    {
        j = 0;
        while(env[i][j] && env[i][j] != '=')
            j++;
        sub = ft_substr(env[i], 0, j);
        if(ft_strcmp(sub, cmd) == 0)
        {
            free(sub);
            return (env[i] + j + 1);
        }
        free(sub);
        i++;
    }
    return NULL;
}

char *get_path(char *cmd, char **env)
{
    int i;
    char *execution;
    char **paths;
    char *div_path;
    char **cmds;

    i = -1;
    paths = ft_split(get_env("PATH", env), ':'); 
    cmds = ft_split(cmd, ' ');
    while(paths[++i])
    {
        div_path = ft_strjoin(paths[i], "/");
        execution = ft_strjoin(div_path, cmds[0]);
        if(access(execution, F_OK | X_OK) == 0)
        {
            ft_free(cmds);
            return (execution);
        }
        free(execution);
    }
    ft_free(paths);
    ft_free(cmds);
    return(cmd);
}