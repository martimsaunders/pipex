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

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		infile;
	int		outfile;
	int		**pipes;
	int		cmd_count;
	pid_t	*pid;
} 			t_pipex;

int		execute_cmd(char *cmd, char **envp);
void	safe_close(int *fd);
void	error_exit(char *msg);
void	close_all(t_pipex *var);
void	free_args(char **newstr);
void	free_pipes(t_pipex *var);
char	*find_path(char *cmd, char **envp);
void	handle_error(char *msg, t_pipex *var);
void	child_process(int infile, int outfile, t_pipex *var);

#endif