/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/02 03:18:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parce_args(char *cmd)
{
	char **args = malloc(10 * sizeof(char *));
	int i = 0;
	char *token = strtok(cmd, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return args;
}

char	*get_cmd_path(char *cmd)
{
	// TODO: GET THE PATH FROM THE ENV
}

int main(int ac, char **av)
{	
	(void)av;
	if (ac != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	int infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		perror("Error opening infile");
		return (1);
	}
	int outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Error opening outfile");
		return (1);
	}

	close(infile);
	close(outfile);
	return (0);
}