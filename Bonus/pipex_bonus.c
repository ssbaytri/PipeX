/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:42 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/16 09:09:04 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	error_msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

static int	execute(t_pipex *pipex, char *envp[])
{
	if (!setup_pipes(pipex))
		return (0);
	if (!fork_children(pipex, envp))
		return (0);
	close_and_wait(pipex);
	return (1);
}

static void	clean_up(t_pipex *pipex)
{
	free_3d(pipex->cmd_args, pipex->cmd_count);
	free_cmd_paths(pipex->cmd_paths, pipex->cmd_count);
	free_pids(pipex);
	free_pipe_fds(pipex);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < check_here_doc(argv[1], &pipex))
		return (error_msg("Error: Invalid number of arguments\n"));
	parse_infile(argv, &pipex);
	parse_outfile(argv[argc - 1], &pipex);
	pipex.cmd_count = argc - 3 - pipex.here_doc;
	fill_args(&pipex, argv, argc);
	fill_paths(&pipex, envp);
	execute(&pipex, envp);
	clean_up(&pipex);
	return (0);
}
