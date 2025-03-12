/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:38:53 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/12 15:50:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isin_env(char *key)
{
	t_env	**env;
	t_env	*node;

	env = get_env_list();
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

	env = get_env_list();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
		{
			if (append)
				node->value = ft_strjoin_env(node->value, value);
			else
				node->value = ft_strdup_env(value);
		}
		node = node->next;
	}
}

static void	handle_export_argument(t_env *node)
{
	if (!node->key || !ft_strcmp(node->key, "_") || !ft_strlen(node->operator))
		return ;
	else if (node->key && ft_isin_env(node->key))
	{
		if (!ft_strcmp(node->operator, "="))
			ft_update_env(node->key, node->value, 0);
		else if (!ft_strcmp(node->operator, "+=") && ft_strcmp(node->value, ""))
			ft_update_env(node->key, node->value, 1);
	}
	else
		ft_lstadd_back_env(node);
}

static int	print_export(void)
{
	t_env	*env;

	env = sort_env();
	while (env)
	{
		if (ft_strcmp(env->key, "_"))
		{
			printf("declare -x %s", env->key);
			if (ft_strcmp(env->value, ""))
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_command command)
{
	t_env	*node;
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
		node = ft_lstnew_env_from_str(arg);
		if (!is_valid_env_key(node->key))
		{
			print_error(1, "export", arg, "not a valid identifier");
			ret = EXIT_FAILURE;
		}
		else
			handle_export_argument(node);
		i++;
	}
	return (ret);
}
