/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:28:58 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 22:23:11 by aelkadir         ###   ########.fr       */
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

	if (oflag & O_CREAT)
		result = open(path, oflag, mode);
	return (ft_error(result));
}
