/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:24:42 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:24:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void    files_and_pipe(char **argv, int *infile, int *outfile, int pipe_fd[2])
{
    *infile = open(argv[1], O_RDONLY);
    if (*infile < 0)
        error_exit("Input file error");
    *outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*outfile < 0)
    {
        close(*infile);
        error_exit("Output file error");
    }
    if (pipe(pipe_fd) < 0)
        handle_error("Pipe error", infile, outfile, pipe_fd);
}

void   pipex(char **argv, char **envp)
{
    int infile;
    int outfile;
    int pipe_fd[2];
    pid_t   pid;

    (void)envp;
    files_and_pipe(argv, &infile, &outfile, pipe_fd);
    pid = fork();
    if (pid < 0)
        handle_error("Proccess ID error", &infile, &outfile, pipe_fd);
    if (pid == 0)
    {
        dup2(infile, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close_all(&infile, &outfile, pipe_fd);
        if (execute_cmd(argv[2], envp))
            handle_error("Command parsing failed", &infile, &outfile, pipe_fd);
    }
    close_all(&infile, &outfile, pipe_fd);
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
        ft_putstr_fd("./pipex infile cmd 1 cmd 2 outfile\n", 2);
        return (1);
    }
    pipex(argv, envp);
    return (0);
}
