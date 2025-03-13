/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:42 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/13 10:25:29 by ssbaytri         ###   ########.fr       */
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

void	print_cmd_args(t_pipex *pipex)
{
	if (!pipex || !pipex->cmd_args)
		return ;
	for (int i = 0; i < pipex->cmd_count; i++)
	{
		printf("Command %d: ", i);
		if (pipex->cmd_args[i])
		{
			for (int j = 0; pipex->cmd_args[i][j]; j++)
			{
				printf("%s ", pipex->cmd_args[i][j]);
			}
		}
		else
		{
			printf("(NULL)");
		}
		printf("\n");
	}
}

void	print_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		printf("Path %d: %s\n", i, pipex->cmd_paths[i]);
		i++;
	}
}

void	ll(void)
{
	system("leaks pipex");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	// atexit(ll);
	(void)envp;
	if (argc < check_here_doc(argv[1], &pipex))
		return (error_msg("Error: Invalid number of arguments\n"));
	parse_infile(argv, &pipex);
	parse_outfile(argv[argc - 1], &pipex);
	pipex.cmd_count = argc - 3 - pipex.here_doc;
	fill_args(&pipex, argv, argc);
	fill_paths(&pipex, envp);
	print_cmd_args(&pipex);
	print_paths(&pipex);
	execute(&pipex, envp);
	free_3d(pipex.cmd_args, pipex.cmd_count);
	free_cmd_paths(pipex.cmd_paths, pipex.cmd_count);
	close(pipex.infile_fd);
	close(pipex.outfile_fd);
	return (0);
}
