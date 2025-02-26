/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:10 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 13:05:26 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_builtin(t_command command)
{
	int		i;
	t_env	**env;

	env = get_env_head();
	i = 1;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		ft_lstremove_env(command.tokens[i]->value);
		i++;
	}
	return (EXIT_SUCCESS);
}
