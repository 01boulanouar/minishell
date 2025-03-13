/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:11:37 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:33:48 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long	ft_atol(const char *str)
{
	long long	num;
	int			signe;

	num = 0;
	signe = 1;
	while (ft_isspace(*str))
		str++;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (1);
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			signe *= -1;
	}
	while (ft_isdigit(*str))
	{
		if (num > num * 10 + (*str - '0'))
			return (LONG_MAX + 1ul);
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((long long)num * signe);
}
