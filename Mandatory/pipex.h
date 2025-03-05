/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:19 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/05 11:08:35 by ssbaytri         ###   ########.fr       */
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

# define ERR_INFILE "Infile\n"
# define ERR_OUTFILE "Outfile\n"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe\n"
# define ERR_CMD "Command not found\n"

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

void		child1(t_pipex *pipex, char *envp[]);
void		child2(t_pipex *pipex, char *envp[]);

#endif