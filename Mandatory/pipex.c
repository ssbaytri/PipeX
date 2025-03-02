/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/02 12:04:39 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parce_args(char *cmd)
{
	char **args = malloc(10 * sizeof(char *));
	int i = 0;
	char *token = strtok(cmd, " ");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return args;
}

char	*get_cmd_path(char *cmd)
{
	char *path = getenv("PATH");
	char *paths = ft_strdup(path);
	char *token = strtok(paths, ":");
	while (token)
	{
		char full_path[1024];
		snprintf(full_path, 1024, "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return ft_strdup(full_path);
		}
		token = strtok(NULL, ":");
	}
	free(paths);
	return NULL;
}

void	excute_cmds(char *cmd, int infd, int outfd)
{
	int pid = fork();
	if (pid == 0)
	{
		dup2(infd, 0);
		dup2(outfd, 1);

		char **args = parce_args(cmd);
		char *cmd_path = get_cmd_path(args[0]);
		if (cmd_path)
		{
			execve(cmd_path, args, NULL);
			perror("Error executing command");
			free(cmd_path);
		}
		else{
			ft_printf("Command not found: %s\n", args[0]);
		}
		free(args);
		exit(1);
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
	
	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("Error creating pipe");
		close(infile);
		close(outfile);
		return (1);
	}
	excute_cmds(av[2], infile, pipefd[1]);
	close(pipefd[1]);

	excute_cmds(av[3], pipefd[0], outfile);
	close(pipefd[0]);

	close(infile);
	close(outfile);
	return (0);
}
