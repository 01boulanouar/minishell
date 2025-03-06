/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:35:52 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/06 21:14:53 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_itoa1(long n)
{
	int		l;
	char	*str;
	int		sign;

	l = len(n);
	str = (char *)ft_malloc_env(l + 1);
	if (!str)
		return (str);
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	str[l--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[l--] = n % 10 + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	return (ft_itoa1(n));
}

int	ft_atoi(const char *nbr)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			sign = -1;
		nbr++;
	}
	while (ft_isdigit(*nbr))
	{
		if (res > (LLONG_MAX - (*nbr - '0')) / 10)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		res = res * 10 + (*nbr - '0');
		nbr++;
	}
	return (res * sign);
}
