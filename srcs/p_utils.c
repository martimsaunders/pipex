/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:25:09 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:25:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    close_all(int *infile, int *outfile, int pipe_fd[2])
{
    safe_close(infile);
    safe_close(outfile);
    safe_close(&pipe_fd[0]);
    safe_close(&pipe_fd[1]);
}

void	free_args(char **newstr)
{
	int	i;

	i = 0;
	while (newstr[i])
		free(newstr[i++]);
	free(newstr);
}