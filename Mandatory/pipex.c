/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:55:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/06 09:50:40 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
}

char	*get_envp_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

int	has_quotes(char const *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	parse_args(t_pipex *pipex, char *argv[])
{
	if (has_quotes(argv[2]))
		pipex->cmd1_args = smart_split(argv[2]);
	else
		pipex->cmd1_args = ft_split(argv[2], ' ');
	if (has_quotes(argv[3]))
		pipex->cmd2_args = smart_split(argv[3]);
	else
		pipex->cmd2_args = ft_split(argv[3], ' ');
}

int	validate_files(t_pipex *pipex, char *argv[])
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("infile");
		return (0);
	}
	pipex->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("outfile");
		close(pipex->infile_fd);
		return (0);
	}
	return (1);
}

int	check_paths(t_pipex *pipex, char *envp[])
{
	char	*path;
	char	**paths;

	path = get_envp_path(envp);
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	pipex->cmd1_path = cmd_path(pipex->cmd1_args[0], paths);
	pipex->cmd2_path = cmd_path(pipex->cmd2_args[0], paths);
	free_2d(paths);
	return (1);
}

void	clean_up(t_pipex *pipex)
{
	free(pipex->cmd1_path);
	free(pipex->cmd2_path);
	free_2d(pipex->cmd1_args);
	free_2d(pipex->cmd2_args);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
}

int	excute(t_pipex *pipex, char *envp[])
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		child1(pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		child2(pipex, envp);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	return (1);
}

void	ll()
{
	system("leaks pipex");
}

int	main(int argc, char *argv[], char *envp[])
{
	atexit(ll);
	t_pipex	pipex;

	if (argc == 5)
	{
		if (!validate_files(&pipex, argv))
			return (1);
		parse_args(&pipex, argv);
		for(int i = 0; pipex.cmd2_args[i]; i++)
			printf("%s\n", pipex.cmd2_args[i]);
		if (!check_paths(&pipex, envp))
		{
			clean_up(&pipex);
			return (1);
		}
		if (!excute(&pipex, envp))
			return (1);
		clean_up(&pipex);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
