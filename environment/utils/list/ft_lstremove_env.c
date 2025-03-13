/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:30 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 17:05:42 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstremove_env(char *key)
{
	t_env	**env;

	env = get_env_list();
	if (!env || !(*env))
		return ;
	while (*env)
	{
		if (!ft_strcmp(key, (*env)->key))
		{
			*env = (*env)->next;
			break ;
		}
		else
			env = &(*env)->next;
	}
}
