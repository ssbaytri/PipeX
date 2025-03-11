/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:02:42 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/11 11:52:12 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ll(void)
{
	system("leaks pipex");
}

int	main(int argc, char *argv[], char *envp[])
{
	// atexit(ll);
	t_pipex pipex;
	(void)envp;
	if (argc < check_here_doc(argv[1], &pipex))
		return (error_msg("Error: Invalid number of arguments\n"));
	parse_infile(argv, &pipex);
	parse_outfile(argv[argc - 1], &pipex);
	return (0);
}
