/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_is_valid_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:11:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 02:46:48 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_is_valid_status(char *str)
{
	size_t	i;

	if (!str || ft_isallspace(str) || !ft_strcmp(str, "-") || !ft_strcmp(str,
			"+"))
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (i < ft_strlen(str) || ft_atol(str) == LONG_MAX + 1ul)
		return (0);
	return (1);
}
