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

#include "pipex_bonus.h"

static void allocate_pipes_pid(t_pipex *var)
{
	int i;

	i = 0;
	var->pipes = malloc(sizeof(int *) * (var->cmd_count - 1));
	if (!var->pipes)
		handle_error("Pipes allocation error", var);
	while (i < var->cmd_count - 1)
	{
		var->pipes[i] = malloc(sizeof(int) * 2);
		if (!var->pipes[i])
		{
			while (--i >= 0)
				free(var->pipes[i]);
			free(var->pipes);
			handle_error("Pipes allocation error", var);
		}
		if (pipe(var->pipes[i]) < 0)
			handle_error("Pipe creation error", var);
		i++;
	}
	var->pid = malloc(sizeof(int) * var->cmd_count);
	if (!var->pid)
		handle_error("Pid creation error", var);
}

static void mid_child_process(char **argv, t_pipex *var, char **envp)
{
	int i;

	i = -1;
	while (++i < var->cmd_count - 2)
	{
		var->pid[i + 1] = fork();
		if (var->pid[i + 1] < 0)
			handle_error("Proccess ID error", var);
		if (var->pid[i + 1] == 0)
		{
			child_process(var->pipes[i][0], var->pipes[i + 1][1], var);
			if (execute_cmd(argv[i + 3], envp))
				handle_error("Command parsing failed", var);
		}
	}
}

static void	files_and_pipe(char **argv, t_pipex *var, int argc)
{
	var->infile = open(argv[1], O_RDONLY);
	if (var->infile < 0)
		error_exit("Input file error");
	var->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var->outfile < 0)
	{
		close(var->infile);
		error_exit("Output file error");
	}
	allocate_pipes_pid(var);
}

static void	pipex(char **argv, char **envp, t_pipex *var)
{
	int i;

	var->pid[0] = fork();
	if (var->pid[0] < 0)
		handle_error("Proccess ID error", var);
	if (var->pid[0] == 0)
	{
		child_process(var->infile, var->pipes[0][1], var);
		if (execute_cmd(argv[2], envp))
			handle_error("Command parsing failed", var);
	}
	mid_child_process(argv, var, envp);
	var->pid[var->cmd_count - 1] = fork();
	if (var->pid[var->cmd_count - 1] < 0)
		handle_error("Proccess ID error", var);
	if (var->pid[var->cmd_count - 1] == 0)
	{
		child_process(var->pipes[var->cmd_count - 2][0], var->outfile, var);
		if (execute_cmd(argv[var->cmd_count + 1], envp))
			handle_error("Command parsing failed", var);
	}
	close_all(var);
	i = -1;
	while (++i < var->cmd_count)
		waitpid(var->pid[i], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex var;

	if (argc < 5)
	{
		ft_putstr_fd("./pipex infile cmd 1 cmd 2 outfile\n", 2);
		return (1);
	}
	ft_memset(&var, 0, sizeof(t_pipex));
	var.cmd_count = argc - 3;
	files_and_pipe(argv, &var, argc);
	pipex(argv, envp, &var);
	free_pipes(&var);
	free(var.pid);
	return (0);
}
