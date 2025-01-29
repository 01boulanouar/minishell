/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:48:17 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/29 20:14:03 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *s, const char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isin(s[i], charset) && (i == 0 || ft_isin(s[i - 1], charset)))
			count++;
		i++;
	}
	return (count);
}

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

static void	ft_locate_end(const char **s, const char *charset)
{
	while (**s && (!ft_isin(**s, charset)))
	{
		if (**s == '"')
		{
			(*s)++;
			while (**s && **s != '"')
				(*s)++;
		}
		if (**s == '\'')
		{
			(*s)++;
			while (**s && **s != '\'')
				(*s)++;
		}
		(*s)++;
	}
}

char	**ft_split(const char *s, const char *charset)
{
	char		**arr;
	const char	*start;
	int			i;

	arr = malloc(sizeof(char *) * (ft_count_words(s, charset) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (ft_isin(*s, charset))
			s++;
		else
		{
			start = s;
			ft_locate_end(&s, charset);
			arr[i] = ft_copy(start, s);
			if (!arr[i])
				return (ft_free(arr, i));
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
