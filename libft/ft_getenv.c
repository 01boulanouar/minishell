/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:37:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:53 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name)
{
	t_env	**env;
	t_env	*tmp;

	env = get_env_list();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
