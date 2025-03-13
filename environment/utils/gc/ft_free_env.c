/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:51:10 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:18:18 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(void)
{
	t_gc	**head;
	t_gc	*curr;
	t_gc	*tmp;

	head = NULL;
	head = ft_gc_env();
	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->ptr);
		free(tmp);
	}
	*head = NULL;
}
