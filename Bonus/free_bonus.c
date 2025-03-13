/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:22:53 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/13 14:23:16 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_cmd_paths(char **arr, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2d(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
}

void	free_3d(char ***arr, int cmd_count)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (i < cmd_count)
		{
			if (arr[i])
				free_2d(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_pids(t_pipex *pipex)
{
	if (pipex->pids)
		free(pipex->pids);
}

void	free_pipe_fds(t_pipex *pipex)
{
	int	i;

	if (pipex->pipe_fds)
	{
		i = 0;
		while (i < pipex->cmd_count - 1)
		{
			free(pipex->pipe_fds[i]);
			i++;
		}
		free(pipex->pipe_fds);
	}
}
