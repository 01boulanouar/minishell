/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 22:55:11 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtin(t_env **env)
{
	t_env	*node;

	node = *env;
	if (!node)
		return (EXIT_FAILURE);
	while (node)
	{
		ft_putstr_fd(node->key, STDOUT_FILENO);
		ft_putchar_fd(EQUAL, STDOUT_FILENO);
		ft_putendl_fd(node->value, STDOUT_FILENO);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
