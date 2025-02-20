/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:02:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/02/20 13:32:33 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
	pid_t pid;
	int status;
	pid = fork();
	if (pid == 0)
	{
		printf("I am the child process with pid = %d\n", getppid());
	}
	else
	{
		printf("I am the parent process with pid of child = %d and my pid = %d\n", pid, getpid());
		wait(&status);
		printf("I am the parent process after the child process has finished\n");
	}
	return (0);
}