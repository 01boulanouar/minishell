/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env_copy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:30:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:01:21 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env_copy(t_env **lst, t_env *new)
{
	t_env	*t;

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
