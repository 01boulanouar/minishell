/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:34:49 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 02:37:35 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_str(void)
{
	int		i;
	char	**arr;
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	arr = ft_malloc(sizeof(char *) * (ft_lstsize_env(node) + 1));
	i = 0;
	while (node)
	{
		arr[i] = ft_strjoin(node->key, ft_strjoin("=", node->value));
		i++;
		node = node->next;
	}
	arr[i] = NULL;
	return (arr);
}
