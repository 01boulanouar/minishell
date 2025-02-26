/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 13:23:45 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_env_head(void)
{
	static t_env	*env;

	return (&env);
}

void	init_env(char **line)
{
	t_env	**env;
	int		i;
	char	*start;
	char	*key;
	char	*value;

	i = 0;
	env = get_env_head();
	while (line[i])
	{
		start = line[i];
		while (*line[i] && *line[i] != EQUAL)
			line[i]++;
		key = ft_copy_env(start, line[i]);
		if (*line[i] == EQUAL)
			line[i]++;
		start = line[i];
		while (*line[i])
			line[i]++;
		value = ft_copy_env(start, line[i]);
		ft_lstadd_back_env(ft_lstnew_env(key, value));
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
