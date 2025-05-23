/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:06:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:19:18 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_core(char const *s1, char const *s2, int space)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	return (ft_strjoin_core(s1, s2, 0));
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	return (ft_strjoin_core(s1, s2, 1));
}
