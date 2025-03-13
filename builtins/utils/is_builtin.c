/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:23:44 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 17:23:54 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command command)
{
	char	*value;

	if (!command.tokens || !command.tokens[0] || !command.tokens[0]->value)
		return (0);
	value = command.tokens[0]->value;
	return (!ft_strcmp(value, "cd") || !ft_strcmp(value, "echo")
		|| !ft_strcmp(value, "env") || !ft_strcmp(value, "exit")
		|| !ft_strcmp(value, "export") || !ft_strcmp(value, "pwd")
		|| !ft_strcmp(value, "unset"));
}
