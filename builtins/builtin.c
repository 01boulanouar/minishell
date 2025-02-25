/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:29:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 18:37:55 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_command command)
{
	char	*value;

	value = command.tokens[0]->value;
	return (!ft_strcmp(value, "cd") || !ft_strcmp(value, "echo")
		|| !ft_strcmp(value, "env") || !ft_strcmp(value, "exit")
		|| !ft_strcmp(value, "export") || !ft_strcmp(value, "pwd")
		|| !ft_strcmp(value, "unset"));
}

int	exec_builtin(t_command command, t_env *env)
{
	char	*value;

	value = command.tokens[0]->value;
	if (!ft_strcmp(value, "pwd"))
		return (pwd_builtin());
	else if (!ft_strcmp(value, "env"))
		return (env_builtin(env));
	return (EXIT_FAILURE);
}
