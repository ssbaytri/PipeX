/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:47:07 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/05 11:27:26 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pipex *pipex, char *envp[])
{
	dup2(pipex->infile_fd, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	if (pipex->cmd1_path)
		execve(pipex->cmd1_path, pipex->cmd1_args, envp);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(pipex->cmd1_args[0], 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	child2(t_pipex *pipex, char *envp[])
{
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	if (pipex->cmd2_path)
		execve(pipex->cmd2_path, pipex->cmd2_args, envp);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(pipex->cmd1_args[0], 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
