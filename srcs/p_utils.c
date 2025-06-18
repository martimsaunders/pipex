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

#include "pipex.h"

void	close_all(t_pipex *var)
{
	safe_close(&var->infile);
	safe_close(&var->outfile);
	safe_close(&var->pipe_fd[0]);
	safe_close(&var->pipe_fd[1]);
}

void	free_args(char **newstr)
{
	int	i;

	i = 0;
	while (newstr[i])
		free(newstr[i++]);
	free(newstr);
}
