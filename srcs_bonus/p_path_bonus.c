/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_path.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/17 13:25:22 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:25:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*find_path_envp(char **envp)
{
	char *path;
	int i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	return (path);
}

char	*find_path(char *cmd, char **envp)
{
	char *first_path;
	char *full_path;
	char **path;
	char *temp;
	int	i;

	i = 0;
	first_path = find_path_envp(envp);
	path = ft_split(first_path, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (free_args(path), full_path);
		free(full_path);
		i++;
	}
	return (free_args(path), NULL);
}

int	execute_cmd(char *cmd, char **envp)
{
	char **cmd_args;
	char *path;

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
