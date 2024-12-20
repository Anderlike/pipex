/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:44:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/19 17:44:47 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "./ft_printf/ft_printf.h"
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

void ft_free(char **target);
char *get_env(char *cmd, char **env);
char *get_path(char *cmd, char **env);
int open_file(char *file, int read);


#endif