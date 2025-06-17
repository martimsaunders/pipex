/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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

void    error_exit(char *msg);
void safe_close(int *fd);
void    handle_error(char *msg, int *infile, int *outfile, int pipe_fd[2]);
void    close_all(int *infile, int *outfile, int pipe_fd[2]);
void	free_args(char **newstr);
int execute_cmd(char *cmd, char **envp);

#endif