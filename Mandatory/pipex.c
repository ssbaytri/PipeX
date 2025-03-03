/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/03 08:35:13 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	validate_files(t_pipex *pipex, char *argv[])
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("infile");
		return (0);
	}
	pipex->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("outfile");
		close(pipex->infile_fd);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	(void)envp;
	if (argc == 5)
	{
		if (!validate_files(&pipex, argv))
			return (1);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
