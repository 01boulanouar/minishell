/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:04:55 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:02:26 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_env(char *key, char *value)
{
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
			node->value = ft_strjoin_env(node->value, value);
		node = node->next;
	}
}
