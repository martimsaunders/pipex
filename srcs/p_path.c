/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_path.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:25:22 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:25:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *find_path(char *cmd, char **envp)
{
    
}

int execute_cmd(char *cmd, char **envp)
{
    char    **cmd_args;
    char    *path;

    cmd_args = ft_split(cmd, ' ');
    if (!cmd_args)
        return (1);
    path = find_path(cmd_args[0], envp);
    if (!path)
        return (free_args(cmd_args), 1);
    execve(path, cmd_args, envp);
    free(path);
    free_args(cmd_args);
    return (1);
}