/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:17:13 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/11 11:50:30 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_infile(char *argv[], t_pipex *pipex)
{
	if (!ft_strcmp("here_doc", argv[1]))
		here_doc(argv[2], pipex);
	else
	{
		pipex->infile_fd = open(argv[1], O_RDONLY);
		if (pipex->infile_fd < 0)
			perror_msg("infile");
	}
}

void	parse_outfile(char *outfile, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex->outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile_fd < 0)
		perror_msg("outfile");
}
