/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:58:36 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/06 21:10:01 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_gc	**get_head(void)
{
	static t_gc	*head;

	return (&head);
}

void	*ft_malloc_env(size_t size)
{
	t_gc	**head;
	t_gc	*new_node;
	void	*ptr;

	head = get_head();
	ptr = malloc(size);
	if (!ptr)
		exit(1);
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		exit(1);
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
	return (ptr);
}

void	ft_free_env(void)
{
	t_gc	**head;
	t_gc	*curr;
	t_gc	*tmp;

	head = NULL;
	head = get_head();
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
