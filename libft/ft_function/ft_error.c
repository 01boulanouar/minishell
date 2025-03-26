/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:01:55 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 23:34:05 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int result)
{
	if (result == -1)
	{
		// ft_exit(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (result);
}
