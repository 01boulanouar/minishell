/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:03:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 17:03:51 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env *new)
{
	t_env	*t;
	t_env	**lst;

	lst = get_env_list();
	if (!lst || !new)
		return ;
	t = (*lst);
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (t->next)
			t = t->next;
		t->next = new;
	}
}
