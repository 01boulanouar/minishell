/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:14:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/02 17:46:01 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isin(const char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isin(s[i], accept))
		i++;
	return (i);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_isin(s[i], reject))
		i++;
	return (i);
}

char	*ft_copy(const char *start, const char *end)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(end - start + 1);
	if (!copy)
		return (NULL);
	while (i < end - start)
	{
		copy[i] = start[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
