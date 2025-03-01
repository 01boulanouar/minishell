/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:54:54 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/01 13:34:04 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_copy_env(const char *start, const char *end)
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

char	*ft_strdup_env(const char *s1)
{
	char	*s2;
	char	*s2_start;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	s2 = malloc(s1_len + 1);
	if (!s2)
		return (NULL);
	s2_start = s2;
	while (*s1)
		*(s2++) = *(s1++);
	*s2 = '\0';
	return (s2_start);
}

char	*ft_strjoin_env(char const *s1, char const *s2)
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
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = '\0';
	return (str);
}
