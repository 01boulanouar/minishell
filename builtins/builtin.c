/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:29:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 13:05:50 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_builtin(t_command command)
{
	char	*value;

	if (!command.tokens || !command.tokens[0])
		return (EXIT_FAILURE);
	value = command.tokens[0]->value;
	if (!ft_strcmp(value, "cd"))
		return (cd_builtin());
	if (!ft_strcmp(value, "echo"))
		return (echo_builtin(command));
	else if (!ft_strcmp(value, "env"))
		return (env_builtin(command));
	else if (!ft_strcmp(value, "exit"))
		return (exit_builtin());
	else if (!ft_strcmp(value, "export"))
		return (export_builtin());
	else if (!ft_strcmp(value, "pwd"))
		return (pwd_builtin());
	else if (!ft_strcmp(value, "unset"))
		return (unset_builtin(command));
	return (EXIT_FAILURE);
}
