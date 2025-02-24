/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:02:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/02/24 21:01:51 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main() {
    pid_t pid;

    pid = 9;
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");    
    printf("Hello1, I am main process (before fork). My PID is %d.\n", getpid());
    // Create a child process using fork()
    pid = fork();
    printf("------------------------------------\n");     
    printf("Hello1, I am main process (after fork). My PID is %d.\n", getpid());
    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork2 failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello1, I am the child process! My PID is %d, and my child's PID is %d\n", getpid(), pid);
    } else {
        // Parent process
        printf("Hello1, I am the parent process! My PID is %d, and my child's PID is %d.\n", getpid(), pid);
    }

    return 0;
}