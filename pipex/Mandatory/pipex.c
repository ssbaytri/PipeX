/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/16 10:09:13 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	parse_args(t_pipex *pipex, char *argv[])
{
	pipex->cmd1_args = smart_split(argv[2]);
	pipex->cmd2_args = smart_split(argv[3]);
}

static void	clean_up(t_pipex *pipex)
{
	free(pipex->cmd1_path);
	free(pipex->cmd2_path);
	free_2d(pipex->cmd1_args);
	free_2d(pipex->cmd2_args);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		validate_files(&pipex, argv);
		parse_args(&pipex, argv);
		if (!check_paths(&pipex, envp))
		{
			clean_up(&pipex);
			return (1);
		}
		excute(&pipex, envp);
		clean_up(&pipex);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
