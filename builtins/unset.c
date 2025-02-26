/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:10 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 10:18:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_builtin(t_command command, t_env **env)
{
	int	i;

	i = 1;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		ft_lstremove_env(env, command.tokens[i]->value);
		i++;
	}
	return (EXIT_SUCCESS);
}
