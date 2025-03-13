/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:05:07 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:06:54 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
