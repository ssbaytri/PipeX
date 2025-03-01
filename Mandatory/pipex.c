/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/01 23:03:29 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int main(int ac, char **av)
{	
	(void)av;
	if (ac != 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 outfile");
		return (1);
	}
	char *line;
	line = get_next_line(0);
	while (line)
	{
		ft_printf("%s\n", line);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (0);
}