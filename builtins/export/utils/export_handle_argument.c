/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handle_argument.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:33:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:15:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_handle_argument(t_env *node)
{
	if (!node->key || !ft_strcmp(node->key, "_") || !ft_strlen(node->operator))
		return ;
	else if (node->key && ft_isin_env(node->key))
	{
		if (!ft_strcmp(node->operator, "="))
			ft_update_env(node->key, node->value);
		else if (!ft_strcmp(node->operator, "+=") && ft_strcmp(node->value, ""))
			ft_append_env(node->key, node->value);
	}
	else
		ft_lstadd_back_env(node);
}
