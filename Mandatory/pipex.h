/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:46:19 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/03 07:45:21 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_pipex
{
    int     infile_fd;
    int     outfile_fd;
    char    **cmd1_args;
    char    **cmd2_args;
    char    *cmd1_path;
    char    *cmd2_path;
} t_pipex;

# endif