/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 17:05:13 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_env *env)
{
	size_t	size;

	if (!env)
		return (0);
	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
