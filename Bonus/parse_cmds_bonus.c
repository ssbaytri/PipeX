/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:00:34 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/12 10:19:10 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fill_args(t_pipex *pipex, char *argv[], int argc)
{
	int	i;
	int	j;

	pipex->cmd_args = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmd_args)
	{
		exit(error_msg("Error: malloc failed\n"));
		exit(1);
	}
	i = pipex->cmd_start;
	j = 0;
	while (i < argc - 1)
	{
		pipex->cmd_args[j] = smart_split(argv[i]);
		i++;
		j++;
	}
}

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

int	fill_paths(t_pipex *pipex, char *envp[])
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	pipex->cmd_paths = malloc(sizeof(char *) * pipex->cmd_count);
	if (!pipex->cmd_paths)
		return (error_msg("Error: malloc failed\n"), 0);
	path = get_envp_path(envp);
	if (!path)
		return (error_msg("Error: PATH not found in envp\n"), 0);
	paths = ft_split(path, ':');
	if (!paths)
		return (error_msg("Error: malloc failed\n"), 0);
	while (i < pipex->cmd_count)
	{
		if (pipex->cmd_args[i] && pipex->cmd_args[i][0])
			pipex->cmd_paths[i] = cmd_path(pipex->cmd_args[i][0], paths);
		else
			pipex->cmd_paths[i] = NULL;
		i++;
	}
	free_2d(paths);
	return (1);
}
