/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:01 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 17:02:24 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_env *node)
{
	int		old_shlvl;
	int		new_shlvl;
	char	*shlvl;

	old_shlvl = ft_atoi(node->value);
	new_shlvl = old_shlvl + 1;
	shlvl = ft_itoa(new_shlvl);
	node->value = ft_strdup_env(shlvl);
}
