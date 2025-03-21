/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:47:07 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/16 10:09:47 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(t_pipex *pipex, char *envp[])
{
	dup2(pipex->infile_fd, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	if (pipex->cmd1_path)
		execve(pipex->cmd1_path, pipex->cmd1_args, envp);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(pipex->cmd1_args[0], 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

static void	child2(t_pipex *pipex, char *envp[])
{
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	if (pipex->cmd2_path)
		execve(pipex->cmd2_path, pipex->cmd2_args, envp);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(pipex->cmd2_args[0], 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

int	excute(t_pipex *pipex, char *envp[])
{
	int	status1;
	int	status2;

	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	pipex->pid1 = fork();
	if (pipex->pid1 == 0 && pipex->infile_fd > 0)
		child1(pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0 && pipex->outfile_fd > 0)
		child2(pipex, envp);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid1, &status1, 0);
	waitpid(pipex->pid2, &status2, 0);
	if (WIFEXITED(status1) && WEXITSTATUS(status1) == 127)
		exit(127);
	if (WIFEXITED(status2) && WEXITSTATUS(status2) == 127)
		exit(127);
	return (1);
}
