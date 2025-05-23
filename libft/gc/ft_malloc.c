/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:08:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 01:09:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t size)
{
	t_gc	**head;
	t_gc	*new_node;
	void	*ptr;

	head = ft_gc();
	ptr = malloc(size);
	if (!ptr)
		ft_exit(1);
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		ft_exit(1);
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
	return (ptr);
}
