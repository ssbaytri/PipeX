/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:32:16 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/13 10:23:05 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(t_pipex *pipex, char *envp[], int i)
{
	// Redirect stdin
	if (i == 0)
		dup2(pipex->infile_fd, STDIN_FILENO);
	else
		dup2(pipex->pipe_fds[i - 1][0], STDIN_FILENO);
	// Redirect stdout
	if (i == pipex->cmd_count - 1)
		dup2(pipex->outfile_fd, STDOUT_FILENO);
	else
		dup2(pipex->pipe_fds[i][1], STDOUT_FILENO);
	// Close all pipe fds in child
	for (int j = 0; j < pipex->cmd_count - 1; j++)
	{
		close(pipex->pipe_fds[j][0]);
		close(pipex->pipe_fds[j][1]);
	}
	// Execute or fail
	if (!pipex->cmd_paths[i] || !pipex->cmd_args[i])
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		if (pipex->cmd_args[i] && pipex->cmd_args[i][0])
			ft_putstr_fd(pipex->cmd_args[i][0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp);
	perror("pipex: execve");
	exit(1);
}

int	execute(t_pipex *pipex, char *envp[])
{
	int	i;

	// Allocate pipe_fds (N-1 pipes)
	if (pipex->cmd_count > 1)
	{
		pipex->pipe_fds = malloc(sizeof(int *) * (pipex->cmd_count - 1));
		if (!pipex->pipe_fds)
			return (0);
		for (i = 0; i < pipex->cmd_count - 1; i++)
		{
			pipex->pipe_fds[i] = malloc(sizeof(int) * 2);
			if (!pipex->pipe_fds[i] || pipe(pipex->pipe_fds[i]) == -1)
				return (0);
		}
	}
	// Allocate pids (N commands)
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		return (0);
	// Fork N children
	for (i = 0; i < pipex->cmd_count; i++)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			return (0);
		if (pipex->pids[i] == 0)
			child_process(pipex, envp, i);
	}
	// Parent closes all pipe fds
	for (i = 0; i < pipex->cmd_count - 1; i++)
	{
		close(pipex->pipe_fds[i][0]);
		close(pipex->pipe_fds[i][1]);
	}
	// Wait for all children
	for (i = 0; i < pipex->cmd_count; i++)
		waitpid(pipex->pids[i], NULL, 0);
	return (1);
}
