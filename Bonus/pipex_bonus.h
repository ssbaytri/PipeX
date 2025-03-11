/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:45 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/11 14:27:18 by ssbaytri         ###   ########.fr       */
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
	int		cmd_start;
}			t_pipex;

int			error_msg(char *err);
void		perror_msg(char *err);

int			process_tokens(char const *s, char **arr, size_t *i, size_t *j);
char		**smart_split(char const *s);

int			check_here_doc(char *farg, t_pipex *pipex);
void		here_doc(char *limiter, t_pipex *pipex);
void		parse_infile(char *argv[], t_pipex *pipex);
void		parse_outfile(char *outfile, t_pipex *pipex);

void		fill_args(t_pipex *pipex, char *argv[], int argc);

#endif