/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:42 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/09 08:31:35 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int main(int argc, char *argv[], char *envp[])
{
	t_pipex pipex;
	(void)envp;
	if (argc < check_here_doc(argv[1], &pipex))
		return (error_msg("Error: Invalid number of arguments\n"));
}