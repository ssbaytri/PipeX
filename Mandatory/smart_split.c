/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:01:56 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/06 09:15:47 by ssbaytri         ###   ########.fr       */
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
		{
			count++;
			i++; // Skip opening quote
			while (s[i] && s[i] != s[i - 1])
				i++;
			if (s[i])
				i++; // Skip closing quote
			else
				break; // Unmatched, rest is one token
		}
		else if (s[i])
		{
			count++;
			while (s[i] && s[i] != ' ')
				i++;
		}
	}
	return (count);
}

char	**smart_split(char const *s)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	start;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\'' || s[i] == '"')
		{
			start = i + 1;
			i++;
			while (s[i] && s[i] != s[start - 1])
				i++;
			if (s[i]) // Matched quote
			{
				arr[j] = ft_substr(s, start, i - start);
				i++; // Skip closing quote
			}
			else // Unmatched quote
				arr[j] = ft_substr(s, start - 1, i - (start - 1)); // Include quote
			if (!arr[j++])
				return (free_split(arr, j - 1));
		}
		else if (s[i])
		{
			start = i;
			while (s[i] && s[i] != ' ')
				i++;
			arr[j] = ft_substr(s, start, i - start);
			if (!arr[j++])
				return (free_split(arr, j - 1));
		}
	}
	arr[j] = NULL;
	return (arr);
}
