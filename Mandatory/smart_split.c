/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:01:56 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/08 05:11:59 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**free_split(char **arr, size_t j)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (i <= j)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	return (NULL);
}

static void	handle_quotes(char const *s, size_t *i, size_t *count)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		(*count)++;
		(*i)++;
		while (s[*i] && s[*i] != s[(*i) - 1])
			(*i)++;
		if (s[*i])
			(*i)++;
		else
			return ;
	}
}

static size_t	count_tokens(char const *s)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\'' || s[i] == '"')
			handle_quotes(s, &i, &count);
		else if (s[i])
		{
			count++;
			while (s[i] && s[i] != ' ')
				i++;
		}
	}
	return (count);
}

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

static int	process_tokens(char const *s, char **arr, size_t *i, size_t *j)
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

char	**smart_split(char const *s)
{
	char	**arr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	if (!process_tokens(s, arr, &i, &j))
		return (free_split(arr, j - 1));
	arr[j] = NULL;
	return (arr);
}
