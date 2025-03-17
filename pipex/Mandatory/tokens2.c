/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 06:10:48 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/08 06:17:41 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_quoted_token(char const *s, char **arr, size_t *i, size_t *j)
{
	size_t	start;

	start = *i + 1;
	(*i)++;
	while (s[*i] && s[*i] != s[start - 1])
		(*i)++;
	if (s[*i])
	{
		arr[*j] = ft_substr(s, start, *i - start);
		(*i)++;
	}
	else
		arr[*j] = ft_substr(s, start - 1, *i - (start - 1));
	if (!arr[(*j)++])
		return (0);
	return (1);
}

static int	handle_regular_token(char const *s, char **arr, size_t *i,
		size_t *j)
{
	size_t	start;

	start = *i;
	while (s[*i] && s[*i] != ' ')
		(*i)++;
	arr[*j] = ft_substr(s, start, *i - start);
	if (!arr[(*j)++])
		return (0);
	return (1);
}

int	process_tokens(char const *s, char **arr, size_t *i, size_t *j)
{
	while (s[*i])
	{
		while (s[*i] == ' ')
			(*i)++;
		if (s[*i] == '\'' || s[*i] == '"')
		{
			if (!handle_quoted_token(s, arr, i, j))
				return (0);
		}
		else if (s[*i])
		{
			if (!handle_regular_token(s, arr, i, j))
				return (0);
		}
	}
	return (1);
}
