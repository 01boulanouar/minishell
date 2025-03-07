/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:35:52 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/07 23:04:26 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_nbrlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		nbr++;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		len;
	long	nbr;

	nbr = (long)n;
	len = ft_nbrlen(nbr);
	dst = ft_malloc(len + 1);
	if (!dst)
		return (NULL);
	if (nbr == 0)
		dst[0] = '0';
	if (nbr < 0)
	{
		dst[0] = '-';
		nbr = -nbr;
	}
	dst[len] = '\0';
	while (nbr)
	{
		len--;
		dst[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (dst);
}

int	ft_atoi(const char *nbr)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (ft_isspace(*nbr))
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
