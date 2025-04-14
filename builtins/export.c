/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:38:53 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/14 13:51:00 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(t_command command)
{
	t_env	*node;
	char	*arg;
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!get_number_of_arguments(command))
		return (export_print());
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arg = command.tokens[i]->value;
		node = ft_lstnew_env_from_str(arg);
		if (!ft_isvalid_env_key(node->key))
		{
			print_error(1, "export", arg, "not a valid identifier");
			ft_set_exit_status(EXIT_FAILURE);
			ret = EXIT_FAILURE;
		}
		else
			export_handle_argument(node);
		i++;
	}
	return (ret);
}

int	export_print(void)
{
	t_env	*env;

	env = ft_lstsort_copy_env();
	while (env)
	{
		if (env->key && ft_strcmp(env->key, "_"))
		{
			printf("declare -x %s", env->key);
			if (env->operator && !ft_strcmp(env->operator, "=") && env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

void	export_handle_argument(t_env *node)
{
	if (!node->key || !ft_strcmp(node->key, "_"))
		return ;
	else if (node->key && ft_isin_env(node->key))
	{
		if (!ft_strcmp(node->operator, "="))
			ft_update_env(node->key, node->value);
		else if (!ft_strcmp(node->operator, "+="))
			ft_append_env(node->key, node->value);
	}
	else
		ft_lstadd_back_env(node);
}
