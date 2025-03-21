/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:45 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/16 07:51:31 by ssbaytri         ###   ########.fr       */
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

int			process_tokens(char const *s, char **arr, size_t *i, size_t *j);
char		**smart_split(char const *s);

void		free_2d(char **arr);
void		free_3d(char ***arr, int cmd_count);
void		free_cmd_paths(char **arr, int cmd_count);
void		free_pids(t_pipex *pipex);
void		free_pipe_fds(t_pipex *pipex);

int			check_here_doc(char *farg, t_pipex *pipex);
void		here_doc(char *limiter, t_pipex *pipex);
int			parse_infile(char *argv[], t_pipex *pipex);
int			parse_outfile(char *outfile, t_pipex *pipex);

void		fill_args(t_pipex *pipex, char *argv[], int argc);
int			fill_paths(t_pipex *pipex, char *envp[]);

int			setup_pipes(t_pipex *pipex);
int			fork_children(t_pipex *pipex, char *envp[]);
void		close_and_wait(t_pipex *pipex);

#endif