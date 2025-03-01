/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/01 12:05:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_env_head(void)
{
	static t_env	*env;

	return (&env);
}

int	is_valid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != UNDERSCORE)
		return (0);
	while (ft_isvalid(key[i]))
		i++;
	return (ft_strlen(key) == i);
}

void	init_env(char **line)
{
	t_env	*node;
	int		i;

	i = 0;
	while (line[i])
	{
		node = ft_lstnew_env_from_str(line[i]);
		ft_lstadd_back_env(node);
		i++;
	}
}

char	*ft_getenv(char *name)
{
	t_env	**env;
	t_env	*tmp;

	env = get_env_head();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
