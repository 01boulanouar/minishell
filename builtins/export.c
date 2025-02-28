/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:09 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/28 15:11:07 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_builtin(t_command command)
{
	t_env	**env;
	char	*arg;
	char	**pair;
	char	*key;
	char	*value;
	int		ret;
	int		i;

	ret = EXIT_SUCCESS;
	env = get_env_head();
	i = 1;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arg = command.tokens[i]->value;
		pair = get_key_value(arg);
		key = pair[0];
		value = pair[1];
		if (!is_valid_env_key(key))
		{
			printf("export: `%s': not a valid identifier\n", arg);
			ret = EXIT_FAILURE;
		}
		else
			ft_lstadd_back_env(ft_lstnew_env(key, value));
		i++;
	}
	return (ret);
}

// do export without =  does nothing
// do export = (overwrite)
// do export '_' does nothing
// do export += (append)
// do export show sorted list
// make lexer join stuff
