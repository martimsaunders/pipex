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

static void	last_process(char **argv, t_pipex *var, char **envp, int argc)
{
	var->pid = fork();
	if (var->pid < 0)
		handle_error("Process ID error", var);
	if (var->pid == 0)
	{
		open_outfile(argv, argc, var);
		child_process(var->infile, var->outfile, var);
		close(var->infile);
		close(var->outfile);
		if (execute_cmd(argv[argc - 2], envp))
			handle_error("Command parsing failed", var);
	}
	close(var->infile);
	waitpid(var->pid, NULL, 0);
}

static void	mid_child_process(char **argv, t_pipex *var, char **envp)
{
	int	i;

	i = 1;
	while (i < var->cmd_count - 1)
	{
		if (pipe(var->pipes) < 0)
			handle_error("Pipe error", var);
		var->pid = fork();
		if (var->pid < 0)
			handle_error("Process ID error", var);
		if (var->pid == 0)
		{
			close(var->pipes[0]);
			child_process(var->infile, var->pipes[1], var);
			close(var->infile);
			close(var->pipes[1]);
			if (execute_cmd(argv[var->first_cmd + i], envp))
				handle_error("Command parsing failed", var);
		}
		close(var->infile);
		close(var->pipes[1]);
		var->infile = var->pipes[0];
		waitpid(var->pid, NULL, 0);
		i++;
	}
}

static void	open_infile(char **argv, t_pipex *var)
{
	var->infile = open(argv[1], O_RDONLY);
	if (var->infile < 0)
		perror("Input file error");
}

static void	pipex(char **argv, char **envp, t_pipex *var, int argc)
{
	if (pipe(var->pipes) < 0)
		handle_error("Pipe error", var);
	var->pid = fork();
	if (var->pid < 0)
		handle_error("Process ID error", var);
	if (var->pid == 0)
	{
		close(var->pipes[0]);
		child_process(var->infile, var->pipes[1], var);
		close(var->infile);
		close(var->pipes[1]);
		if (execute_cmd(argv[var->first_cmd], envp))
			handle_error("Command parsing failed", var);
	}
	close(var->pipes[1]);
	var->infile = var->pipes[0];
	waitpid(var->pid, NULL, 0);
	mid_child_process(argv, var, envp);
	last_process(argv, var, envp, argc);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	var;

	if (argc < 5)
	{
		ft_putstr_fd("./pipex infile cmd 1 cmd 2 outfile\n", 2);
		ft_putstr_fd("./pipex here_doc lim cmd 1 cmd 2 outfile\n", 2);
		return (1);
	}
	ft_memset(&var, 0, sizeof(t_pipex));
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		var.cmd_count = argc - 4;
		here_doc(argv, &var);
		var.first_cmd = 3;
	}
	else
	{
		var.cmd_count = argc - 3;
		open_infile(argv, &var);
		var.first_cmd = 2;
	}
	pipex(argv, envp, &var, argc);
	close_all(&var);
	return (0);
}
