/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:09:22 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/26 15:13:05 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char **argv, t_pipex *var)
{
	char	*line;
	int		limiter;
	int		temp_fd[2];

	if (pipe(temp_fd) < 0)
		handle_error("Pipe creation error", var);
	limiter = ft_strlen(argv[2]);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, argv[2], limiter))
	{
		ft_putstr_fd(line, temp_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(temp_fd[1]);
	var->infile = temp_fd[0];
	var->def_out = 1;
}
