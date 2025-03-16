/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:09:02 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/16 08:18:16 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_here_doc(char *farg, t_pipex *pipex)
{
	if (farg && !ft_strcmp("here_doc", farg))
	{
		pipex->cmd_start = 3;
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->cmd_start = 2;
		pipex->here_doc = 0;
		return (5);
	}
}

void	here_doc(char *limiter, t_pipex *pipex)
{
	int		fd;
	char	*buffer;

	fd = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror("here_doc");
	while (1)
	{
		ft_printf("here_doc>");
		buffer = get_next_line(0);
		if (!buffer || (!ft_strncmp(buffer, limiter, ft_strlen(limiter))
			&& buffer[ft_strlen(limiter)] == '\n'))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	pipex->infile_fd = open("/tmp/here_doc", O_RDONLY);
	if (pipex->infile_fd < 0)
		unlink("/tmp/here_doc");
}
