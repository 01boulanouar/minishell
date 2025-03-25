/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:01:55 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 03:06:46 by moboulan         ###   ########.fr       */
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
