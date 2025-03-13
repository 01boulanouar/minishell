/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:01:26 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 15:01:41 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isin_env(char *key)
{
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
			return (1);
		node = node->next;
	}
	return (0);
}
