/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:42:58 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:19:00 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
