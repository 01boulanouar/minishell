/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:54:54 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:06:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
