/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:32:25 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/16 23:41:12 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_print(void)
{
	t_env	*env;

	env = ft_lstsort_copy_env();
	while (env)
	{
		if (env->key && ft_strcmp(env->key, "_"))
		{
			printf("declare -x %s", env->key);
			if (!ft_strcmp(env->operator, "="))
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
