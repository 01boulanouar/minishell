/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:10 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:16:18 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_command command)
{
	char	*arg;
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	i = 1;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arg = command.tokens[i]->value;
		if (!ft_isvalid_env_key(arg))
		{
			print_error(1, "unset", arg, "not a valid identifier");
			ret = EXIT_FAILURE;
		}
		else
			ft_lstremove_env(arg);
		i++;
	}
	return (ret);
}
