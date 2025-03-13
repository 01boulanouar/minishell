/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstenv_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:46 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:16:10 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstenv_copy(void)
{
	t_env	**env;
	t_env	*env_copy;
	t_env	*node;
	t_env	*new;

	env = get_env_list();
	if (!env)
		return (NULL);
	env_copy = NULL;
	node = *env;
	while (node)
	{
		new = ft_lstnew_env(node->key, node->operator, node->value);
		ft_lstadd_back_env_copy(&env_copy, new);
		node = node->next;
	}
	return (env_copy);
}
