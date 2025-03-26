/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:09:15 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 23:04:48 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void)
{
	t_gc	**head;
	t_gc	*curr;
	t_gc	*temp;

	head = NULL;
	head = ft_gc();
	curr = *head;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp->ptr);
		temp->ptr = NULL;
		free(temp);
		temp = NULL;
	}
	*head = NULL;
}
