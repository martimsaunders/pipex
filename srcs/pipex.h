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
	int		infile;
	int		first_cmd;
	int		outfile;
	int		def_out;
	int		pipes[2];
	int		cmd_count;
	pid_t	pid;
}			t_pipex;

int			count_plicas(char const *s);
int			execute_cmd(char *cmd, char **envp);
int			toggle_quotes(int in_quotes, char c, char *quote_char);
void		safe_close(int *fd);
void		error_exit(char *msg);
void		close_all(t_pipex *var);
void		free_args(char **newstr);
char		*find_path(char *cmd, char **envp);
void		free_split(char **newstr, size_t i);
void		here_doc(char **argv, t_pipex *var);
void		handle_error(char *msg, t_pipex *var);
void		open_outfile(char **argv, int argc, t_pipex *var);
void		child_process(int infile, int outfile, t_pipex *var);
char		**ft_split_with_quotes(char const *s, char c, int i, int j);

#endif