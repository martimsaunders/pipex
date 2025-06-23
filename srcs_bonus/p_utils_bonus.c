/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/17 13:25:09 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:25:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_all(t_pipex *var)
{
	int i;

	i = -1;
	safe_close(&var->infile);
	safe_close(&var->outfile);
	while (++i < var->cmd_count - 1)
	{
		safe_close(&var->pipes[i][0]);
		safe_close(&var->pipes[i][1]);
	}
}

void	free_args(char **newstr)
{
	int	i;

	i = 0;
	while (newstr[i])
		free(newstr[i++]);
	free(newstr);
}

void	free_pipes(t_pipex *var)
{
	int i;

	i = 0;
	while (i < var->cmd_count - 1)
	{
		free(var->pipes[i]);
		i++;
	}
	free(var->pipes);
	var->pipes = NULL;
}

void	child_process(int infile, int outfile, t_pipex *var)
{
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close_all(var);
}

void	safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}
