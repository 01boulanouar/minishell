/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:28:58 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 22:40:44 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(const char *path, int oflag)
{
	int		result;

	result = open(path, oflag);
	if (result == -1)
	{
		print_error(1, (char *)path, NULL, strerror(errno));
		ft_set_exit_status(EXIT_FAILURE);
	}
	return (result);
}

int	ft_open_create(const char *path, int oflag, int mode)
{
	int		result;
	
	result = open(path, oflag, mode);
	if (result == -1)
	{
		print_error(1, (char *)path, NULL, strerror(errno));
		ft_set_exit_status(EXIT_FAILURE);
	}
	return (result);
}
