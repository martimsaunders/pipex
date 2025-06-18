/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/17 13:24:42 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:24:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int infile, int outfile, t_pipex *var)
{
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close_all(var);
}

static void	files_and_pipe(char **argv, t_pipex *var)
{
	var->infile = open(argv[1], O_RDONLY);
	if (var->infile < 0)
		error_exit("Input file error");
	var->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var->outfile < 0)
	{
		close(var->infile);
		error_exit("Output file error");
	}
	if (pipe(var->pipe_fd) < 0)
		handle_error("Pipe error", var);
}

static void	pipex(char **argv, char **envp, t_pipex *var)
{
	files_and_pipe(argv, var);
	var->pid[0] = fork();
	if (var->pid[0] < 0)
		handle_error("Proccess ID error", var);
	if (var->pid[0] == 0)
	{
		child_process(var->infile, var->pipe_fd[1], var);
		if (execute_cmd(argv[2], envp))
			handle_error("Command parsing failed", var);
	}
	var->pid[1] = fork();
	if (var->pid[1] < 0)
		handle_error("Proccess ID error", var);
	if (var->pid[1] == 0)
	{
		child_process(var->pipe_fd[0], var->outfile, var);
		if (execute_cmd(argv[3], envp))
			handle_error("Command parsing failed", var);
	}
	close_all(var);
	waitpid(var->pid[0], NULL, 0);
	waitpid(var->pid[1], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex var;

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd 1 cmd 2 outfile\n", 2);
		return (1);
	}
	ft_memset(&var, 0, sizeof(t_pipex));
	pipex(argv, envp, &var);
	return (0);
}
