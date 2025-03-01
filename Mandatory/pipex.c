/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/01 23:54:21 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	excute_cmd(char *cmd, int infd, int outfd)
{
	int pid = fork();
	if (pid == 0)
	{
		dup2(infd, STDIN_FILENO);
		dup2(outfd, STDOUT_FILENO);
		execve(cmd, NULL, NULL);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("Error forking");
		exit(1);
	}
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