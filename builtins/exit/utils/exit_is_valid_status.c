/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_is_valid_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:11:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:15:37 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_is_valid_status(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (i < ft_strlen(str) || ft_isallspace(str) || (ft_strlen(str) == 1
			&& (str[0] == '-' || str[0] == '+')) || ft_atol(str) == LONG_MAX
		+ 1ul)
		return (0);
	return (1);
}
