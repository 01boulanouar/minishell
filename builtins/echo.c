/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:03 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/11 20:11:30 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_is_n(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !ft_strcmp(str, ""))
		return (0);
	if (str[0] != '-')
		return (0);
	if (str[0] == '-' && str[1])
		str++;
	while (str[i] == 'n')
		i++;
	return (ft_strlen(str) == i);
}

int	echo_builtin(t_command command)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	while (command.tokens[i] && command.tokens[i]->value
		&& echo_is_n(command.tokens[i]->value))
	{
		n_flag++;
		i++;
	}
	while (command.tokens[i] && command.tokens[i]->value)
	{
		if (command.tokens[i]->after_space
			&& !(!ft_strcmp(command.tokens[i]->value, "")
				&& command.tokens[i]->type == t_expanded) && i != (n_flag + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(command.tokens[i]->value, STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
