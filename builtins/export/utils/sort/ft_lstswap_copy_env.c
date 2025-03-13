/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap_copy_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:29:40 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:01:40 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstswap_copy_env(t_env *node, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_operator;

	tmp_key = node->key;
	tmp_value = node->value;
	tmp_operator = node->operator;
	node->key = next->key;
	node->value = next->value;
	node->operator = next->operator;
	next->key = tmp_key;
	next->value = tmp_value;
	next->operator = tmp_operator;
}
