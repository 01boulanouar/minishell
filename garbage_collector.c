/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:58:36 by aelkadir          #+#    #+#             */
/*   Updated: 2025/02/22 15:51:33 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	**get_head(void)
{
	static t_node	*head;

	return (&head);
}

void	*ft_malloc(size_t size)
{
	t_node	**head;
	t_node	*new_node;
	void	*ptr;

	head = get_head();
	ptr = malloc(size);
	if (!ptr)
	{
		printf("malloc failed a jmi");
		exit(1);
	}
	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		printf("malloc failed a jmi");
		exit(1);
	}
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
	return (ptr);
}

void	ft_free(void)
{
	t_node	**head;
	t_node	*curr;
	t_node	*temp;

	head = NULL;
	head = get_head();
	curr = *head;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp->ptr);
		free(temp);
	}
	*head = NULL;
}
