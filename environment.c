/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 10:25:07 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*handle_env(char **line)
{
	t_env	*env;
	int		i;
	char	*start;
	char	*key;
	char	*value;

	i = 0;
	env = NULL;
	while (line[i])
	{
		start = line[i];
		while (*line[i] && *line[i] != EQUAL)
			line[i]++;
		key = ft_copy(start, line[i], 0);
		if (*line[i] == EQUAL)
			line[i]++;
		start = line[i];
		while (*line[i])
			line[i]++;
		value = ft_copy(start, line[i], 0);
		ft_lstadd_back_env(&env, ft_lstnew_env(key, value));
		i++;
	}
	return (env);
}
