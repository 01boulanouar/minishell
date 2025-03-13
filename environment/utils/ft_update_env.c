/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:03:29 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:34:07 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env(char *key, char *value)
{
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
			node->value = ft_strdup_env(value);
		node = node->next;
	}
}
