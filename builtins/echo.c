/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:03 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 12:09:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_builtin(t_command command)
{
	int	i;

	i = 1;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		if (command.tokens[i]->after_space && i != 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(command.tokens[i]->value, STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_FAILURE);
}
