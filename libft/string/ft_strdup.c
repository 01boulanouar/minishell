/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:04:52 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:19:13 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*s2_start;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2 = ft_malloc(s1_len + 1);
	s2_start = s2;
	while (*s1)
		*(s2++) = *(s1++);
	*s2 = '\0';
	return (s2_start);
}
