/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:09 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/28 17:47:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isin_env(char *key)
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

static void	ft_update_env(char *key, char *value, int append)
{
	t_env	**env;
	t_env	*node;
	char	*tmp;

	env = get_env_head();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
		{
			tmp = node->value;
			if (append)
				node->value = ft_strjoin_env(node->value, value);
			else
				node->value = value;
			free(tmp);
		}
		node = node->next;
	}
}

static void	handle_export_argument(char **pair)
{
	char	*key;
	char	*operation;
	char	*value;

	key = pair[0];
	operation = pair[1];
	value = pair[2];
	if (!key || !ft_strcmp(key, "_") || !ft_strlen(operation))
		return (free(key), free(operation), free(value));
	else if (key && ft_isin_env(key))
	{
		if (!ft_strcmp(operation, "="))
			ft_update_env(key, value, 0);
		else if (!ft_strcmp(operation, "+="))
			ft_update_env(key, value, 1);
	}
	else
		ft_lstadd_back_env(ft_lstnew_env(key, value));
	return (free(key), free(operation));
}

static int	print_export(void)
{
	t_env	*env;

	env = sort_env();
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_command command)
{
	char	**pair;
	char	*arg;
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!get_number_of_arguments(command))
		return (print_export());
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arg = command.tokens[i]->value;
		pair = get_key_value(arg);
		if (!is_valid_env_key(pair[0]))
		{
			(free(pair[0]), free(pair[1]), free(pair[2]));
			printf("export: `%s': not a valid identifier\n", arg);
			ret = EXIT_FAILURE;
		}
		else
			handle_export_argument(pair);
		i++;
	}
	return (ret);
}

// overhall printing
// change with put endl
// make lexer join stuff
