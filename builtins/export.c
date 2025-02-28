/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:09 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/28 16:56:59 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isin_env(char *key)
{
	t_env	**env;
	t_env	*node;

	env = get_env_head();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
			return (1);
		node = node->next;
	}
	return (0);
}

void	ft_update_env(char *key, char *value, int append)
{
	t_env	**env;
	t_env	*node;

	env = get_env_head();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
		{
			if (append)
				node->value = ft_strjoin_env(node->value, value);
			else
				node->value = value;
		}
		node = node->next;
	}
}

int	export_builtin(t_command command)
{
	t_env	**env;
	char	*arg;
	char	**pair;
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	env = get_env_head();
	i = 1;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arg = command.tokens[i]->value;
		pair = get_key_value(arg);
		printf("[%s] [%s] [%s]\n", pair[0], pair[1], pair[2]);
		if (!is_valid_env_key(pair[0]))
		{
			printf("export: `%s': not a valid identifier\n", arg);
			ret = EXIT_FAILURE;
		}
		else if (pair[0] && !ft_strlen(pair[1]))
		{
			i++;
			continue ;
		}
		if (ft_isin_env(pair[0]))
		{
			if (!ft_strcmp(pair[1], "="))
				ft_update_env(pair[0], pair[2], 0);
			else if (!ft_strcmp(pair[1], "+="))
				ft_update_env(pair[0], pair[2], 1);
		}
		else
			ft_lstadd_back_env(ft_lstnew_env(pair[0], pair[2]));
		i++;
	}
	return (ret);
}

// do export '_' does nothing
// do export show sorted list
// make lexer join stuff
