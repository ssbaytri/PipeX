/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:02:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/02/25 01:51:00 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
    int fds[2];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        close(fds[0]);
        write(fds[1], "hello", 5);
        close(fds[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fds[1]);
        char str[20];
        read(fds[0], str, 5);
        printf("parent received: %s\n", str);
        close(fds[0]);
        wait(NULL);
    }
    return (0);
}