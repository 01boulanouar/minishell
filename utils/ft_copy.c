/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:54:54 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/05 01:15:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_copy(const char *start, const char *end)
{
	int		i;
	char	*copy;

	i = 0;
	copy = ft_malloc(end - start + 1);
	while (i < end - start)
	{
		copy[i] = start[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_trim(char *line)
{
	const char	*start;
	const char	*end;

	if (!line)
		return (NULL);
	start = line;
	end = line + ft_strlen(line) - 1;
	while (*start && ft_isin(*start, BLANKS))
		start++;
	while (end > start && ft_isin(*end, BLANKS))
		end--;
	return (ft_copy(start, end + 1));
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*s2_start;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	s2 = ft_malloc(s1_len + 1);
	s2_start = s2;
	while (*s1)
		*(s2++) = *(s1++);
	*s2 = '\0';
	return (s2_start);
}

char	*ft_strjoin(char const *s1, char const *s2, int space)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	str = (char *)ft_malloc(len + 2);
	while (*s1)
		str[i++] = *(s1++);
	if (space)
		str[i++] = ' ';
	while (*s2)
		str[i++] = *(s2++);
	str[i] = '\0';
	return (str);
}
