/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:10:40 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 02:21:09 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_print_quotes(char *function)
{
	return (!ft_strcmp(function, "export") || !ft_strcmp(function, "unset"));
}

void	print_error(int print_name, char *function, char *file, char *error)
{
	if (print_name)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (function)
	{
		ft_putstr_fd(function, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (function && file)
	{
		if (should_print_quotes(function))
			ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		if (should_print_quotes(function))
			ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
