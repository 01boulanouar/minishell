/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/28 16:36:11 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_env_head(void)
{
	static t_env	*env;

	return (&env);
}

char	**get_key_value(char *argument)
{
	char	**pair;
	char	*start;

	pair = ft_malloc(sizeof(char *) * 3);
	start = argument;
	while (*argument)
	{
		if (*argument == EQUAL || (*argument == PLUS && (*(argument + 1)
					&& *(argument + 1) == EQUAL)))
			break ;
		argument++;
	}
	pair[0] = ft_copy_env(start, argument);
	start = argument;
	if (*argument == PLUS && (*(argument + 1) && *(argument + 1) == EQUAL))
		argument++;
	if (*argument == EQUAL)
		argument++;
	pair[1] = ft_copy_env(start, argument);
	start = argument;
	while (*argument)
		argument++;
	pair[2] = ft_copy_env(start, argument);
	return (pair);
}

int	is_valid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (key[0] == SINGLE_QUOTE)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != UNDERSCORE)
		return (0);
	while (ft_isalnum(key[i]) || key[i] == UNDERSCORE)
		i++;
	return (ft_strlen(key) == i);
}

void	init_env(char **line)
{
	t_env	**env;
	int		i;
	char	*start;
	char	**pair;

	i = 0;
	env = get_env_head();
	while (line[i])
	{
		start = line[i];
		pair = get_key_value(line[i]);
		ft_lstadd_back_env(ft_lstnew_env(pair[0], pair[2]));
		free(pair[1]);
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
