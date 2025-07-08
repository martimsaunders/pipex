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
	safe_close(&var->pipes[0]);
	safe_close(&var->pipes[1]);
}

void	free_args(char **newstr)
{
	int	i;

	i = 0;
	while (newstr[i])
		free(newstr[i++]);
	free(newstr);
}

void	child_process(int infile, int outfile, t_pipex *var)
{
	if (dup2(infile, STDIN_FILENO) < 0)
		handle_error("Read error", var);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		handle_error("Write error", var);
}

void	safe_close(int *fd)
{
	if (*fd >= 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	open_outfile(char **argv, int argc, t_pipex *var)
{
	if (var->def_out == 0)
	{
		var->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (var->outfile < 0)
			perror("Output file error");
	}
	if (var->def_out == 1)
	{
		var->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (var->outfile < 0)
			perror("Output file error");
	}
}
