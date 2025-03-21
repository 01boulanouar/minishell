/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:28:58 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 22:38:32 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(const char *path, int oflag, ...)
{
	int		result;
	va_list	args;

	va_start(args, oflag);
	if (oflag & O_CREAT)
		result = open(path, oflag, va_arg(args, int));
	else
		result = open(path, oflag);
	va_end(args);
	ft_error(result);
	register_fd(result);
	return result;
}
