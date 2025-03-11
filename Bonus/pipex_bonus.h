/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:45 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/11 11:52:35 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		**pipe_fds;
	pid_t	*pids;
	char	**cmd_paths;
	char	***cmd_args;
	int		here_doc;
	int		cmd_count;
}			t_pipex;

int			error_msg(char *err);
void		perror_msg(char *err);

int			check_here_doc(char *farg, t_pipex *pipex);
void		here_doc(char *limiter, t_pipex *pipex);
void		parse_infile(char *argv[], t_pipex *pipex);
void		parse_outfile(char *outfile, t_pipex *pipex);

#endif