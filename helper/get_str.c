/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:23:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/08 00:01:31 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_command_len(t_command command)
{
	int	i;

	if (!command.tokens)
		return (0);
	i = 0;
	while (command.tokens[i] && command.tokens[i]->value)
		i++;
	return (i);
}

char	**get_command_str(t_command command)
{
	int		i;
	char	**arr;

	arr = ft_malloc(sizeof(char *) * (get_command_len(command) + 1));
	i = 0;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arr[i] = ft_strdup(command.tokens[i]->value);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**get_env_str(void)
{
	int		i;
	char	**arr;
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	arr = ft_malloc(sizeof(char *) * (ft_lstsize(node) + 1));
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
