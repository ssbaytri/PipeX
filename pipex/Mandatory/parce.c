/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 06:25:34 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/11 14:21:47 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_envp_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static char	*cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

int	check_paths(t_pipex *pipex, char *envp[])
{
	char	*path;
	char	**paths;

	path = get_envp_path(envp);
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	pipex->cmd1_path = cmd_path(pipex->cmd1_args[0], paths);
	pipex->cmd2_path = cmd_path(pipex->cmd2_args[0], paths);
	free_2d(paths);
	return (1);
}

int	validate_files(t_pipex *pipex, char *argv[])
{
	pipex->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("outfile");
		return (0);
	}
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("infile");
		return (0);
	}
	return (1);
}
