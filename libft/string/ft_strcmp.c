/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:24 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:20:36 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		r;

	r = 0;
	i = 0;
	while (r == 0)
	{
		if (!(s1[i] || s2[i]))
			break ;
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (r);
}
