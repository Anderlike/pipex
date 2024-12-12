/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:40:36 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/27 15:40:36 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/pipex.h"

void execution(char* cmd, char **env)
{
    char **cmds;
    char *path;

    cmds = ft_split(cmd, ' ');
    path = get_path(cmds[0], env);
    if(execve(path, cmds, env) == -1)
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(cmds[0], 2);
        ft_free(cmds);
        exit(0);
    }
}

void child(char **argv, int *fd, char **env)
{
    int i_fd;

    i_fd = open_file(argv[1], 0);
    dup2(i_fd, 0);
    dup2(fd[1], 1);
    close(fd[0]);
    execution(argv[2], env);
}

void parent(char **argv, int *fd, char **env)
{
    int i_fd;

    i_fd = open_file(argv[4], 1);
    dup2(i_fd, 0);
    dup2(fd[0], 0);
    close(fd[1]);
    execution(argv[3], env);
}

int main(int argc, char **argv, char **env)
{
    if (argc != 5)
    {
        ft_printf("Error\n");
        return (1);
    }
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1)
        exit(-1);
    pid = fork();
    if(pid == -1)
        exit(-1);
    if(!pid)
        child(argv, fd, env);
    parent(argv, fd, env);
    return (0);
}
