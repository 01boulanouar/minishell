/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:03 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:25:17 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_isin(s[i], reject))
		i++;
	return (i);
}
