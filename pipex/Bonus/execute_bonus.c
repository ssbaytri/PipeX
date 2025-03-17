/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:32:16 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/16 08:02:52 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exit_cmd_error(char **args)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	if (args && args[0])
		ft_putstr_fd(args[0], 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

static void	child_process(t_pipex *pipex, char *envp[], int i)
{
	int	j;

	j = 0;
	if (i == 0)
		dup2(pipex->infile_fd, STDIN_FILENO);
	else
		dup2(pipex->pipe_fds[i - 1][0], STDIN_FILENO);
	if (i == pipex->cmd_count - 1)
		dup2(pipex->outfile_fd, STDOUT_FILENO);
	else
		dup2(pipex->pipe_fds[i][1], STDOUT_FILENO);
	while (j < pipex->cmd_count - 1)
	{
		close(pipex->pipe_fds[j][0]);
		close(pipex->pipe_fds[j][1]);
		j++;
	}
	if (!pipex->cmd_paths[i] || !pipex->cmd_args[i])
		exit_cmd_error(pipex->cmd_args[i]);
	execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp);
	perror("pipex: execve");
	exit(1);
}

int	setup_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_count <= 1)
		return (1);
	pipex->pipe_fds = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipe_fds)
		return (0);
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipe_fds[i] || pipe(pipex->pipe_fds[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	fork_children(t_pipex *pipex, char *envp[])
{
	int	i;

	i = 0;
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		return (0);
	while (i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			return (0);
		if (pipex->pids[i] == 0)
		{
			if ((i == 0 && pipex->infile_fd < 0) || (i == pipex->cmd_count - 1
					&& pipex->outfile_fd < 0))
				exit(1);
			child_process(pipex, envp, i);
		}
		i++;
	}
	return (1);
}

void	close_and_wait(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipe_fds[i][0]);
		close(pipex->pipe_fds[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], NULL, 0);
		i++;
	}
}
