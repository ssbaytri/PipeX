/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:00:34 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/12 08:38:09 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fill_args(t_pipex *pipex, char *argv[], int argc)
{
	int i;
	int j;
	
	pipex->cmd_args = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmd_args)
	{
		exit(error_msg("Error: malloc failed\n"));
		exit(1);
	}
	i = pipex->cmd_start;
	j = 0;
	while (i < argc - 1)
	{
		pipex->cmd_args[j] = smart_split(argv[i]);
		i++;
		j++;
	}
}