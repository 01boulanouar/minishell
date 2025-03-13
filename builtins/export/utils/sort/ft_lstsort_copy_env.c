/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_copy_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:47:29 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:32:58 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstsort_copy_env(void)
{
	int		swapped;
	t_env	*env;
	t_env	*node;
	t_env	*tmp;

	env = ft_lstenv_copy();
	swapped = 1;
	tmp = NULL;
	while (swapped)
	{
		swapped = 0;
		node = env;
		while (node->next != tmp)
		{
			if (ft_strcmp(node->key, node->next->key) > 0)
			{
				ft_lstswap_copy_env(node, node->next);
				swapped = 1;
			}
			node = node->next;
		}
		tmp = node;
	}
	return (env);
}
