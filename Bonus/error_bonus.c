/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:17:48 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/09 07:18:49 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	error_msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	perror_msg(char *err)
{
	perror(err);
	exit(1);
}
