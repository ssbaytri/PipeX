/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:19 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/08 07:00:26 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile_fd;
	int		outfile_fd;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
}			t_pipex;

int			process_tokens(char const *s, char **arr, size_t *i, size_t *j);
char		**smart_split(char const *s);
int			excute(t_pipex *pipex, char *envp[]);
int			validate_files(t_pipex *pipex, char *argv[]);
int			check_paths(t_pipex *pipex, char *envp[]);
void		free_2d(char **arr);

#endif