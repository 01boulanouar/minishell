/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_is_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:14 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:28:35 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_is_n(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !ft_strcmp(str, ""))
		return (0);
	if (str[0] == '-')
		str++;
	while (str[i] == 'n')
		i++;
	return (ft_strlen(str) == i);
}
