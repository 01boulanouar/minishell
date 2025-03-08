/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/08 00:02:37 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtin(t_command command)
{
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	if (!node)
		return (EXIT_FAILURE);
	if (get_number_of_arguments(command))
	{
		print_error(0, "env", command.tokens[1]->value, \
			"No such file or directory");
		return (EXIT_FAILURE);
	}
	while (node)
	{
		if (ft_strcmp(node->key, "OLDPWD"))
		{
			ft_putstr_fd(node->key, STDOUT_FILENO);
			ft_putchar_fd(EQUAL, STDOUT_FILENO);
			ft_putendl_fd(node->value, STDOUT_FILENO);
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
