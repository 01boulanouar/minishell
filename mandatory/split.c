/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:48:17 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/29 19:49:02 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_copy(const char *start, const char *end)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(end - start + 1);
	if (!copy)
		return (NULL);
	while (start < end)
	{
		copy[i] = *start;
		start++;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_free(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
	return (NULL);
}

static void	ft_skip(const char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		while (**s && **s != c)
			(*s)++;
	}
}

static char	**ft_malloc(const char *s, const char *charset)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (ft_count_words(s, charset) + 1));
	if (!arr)
		return (NULL);
	return (arr);
}

char	**ft_split(const char *s, const char *charset)
{
	char		**arr;
	char const	*start;
	int			i;

	arr = ft_malloc(s, charset);
	i = 0;
	while (*s)
	{
		if (ft_isin(*s, charset))
			s++;
		else
		{
			start = s;
			ft_skip(&s, '"');
			ft_skip(&s, '\'');
			while (*s && (!ft_isin(*s, charset)))
				s++;
			arr[i] = ft_copy(start, s);
			if (!arr[i])
				return (ft_free(arr, i));
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
