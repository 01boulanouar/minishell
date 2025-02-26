/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 22:46:48 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_command *commands, t_env **env)
{
	int	i;

	i = 0;
	while (i < 1)
	{
		if (is_builtin(commands[i]))
			exec_builtin(commands[i], env);
		i++;
	}
}
