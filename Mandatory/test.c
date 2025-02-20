/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:02:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/02/20 12:16:42 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
	char *args[] = {"cat", "test.c", NULL};
	char *env[] = {NULL};
	if (execve("/bin/cat", args, env) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}