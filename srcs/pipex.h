/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/17 13:26:12 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:26:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libraries/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int infile;
	int outfile;
	int pipe_fd[2];
	pid_t pid[2];
} t_pipex;

int	execute_cmd(char *cmd, char **envp);
void	error_exit(char *msg);
void	safe_close(int *fd);
void	handle_error(char *msg, t_pipex *var);
void	close_all(t_pipex *var);
void	free_args(char **newstr);
char	*find_path(char *cmd, char **envp);

#endif