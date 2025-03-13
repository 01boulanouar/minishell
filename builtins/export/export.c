/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:38:53 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:16:13 by moboulan         ###   ########.fr       */
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
			ret = EXIT_FAILURE;
		}
		else
			export_handle_argument(node);
		i++;
	}
	return (ret);
}
