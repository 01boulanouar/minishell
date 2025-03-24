/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:28:58 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/24 22:33:17 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(const char *path, int oflag)
{
	int		result;

	result = open(path, oflag);
	return (ft_error(result));
}

int	ft_open_create(const char *path, int oflag, int mode)
{
	int		result;
	
	result = open(path, oflag, mode);
	return (ft_error(result));
}
