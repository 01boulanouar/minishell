/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:36:47 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 10:37:18 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew_token(char *value, t_token_type type, int after_space,
		int expanded)
{
	t_token	*t;

	t = ft_malloc(sizeof(t_token));
	t->value = value;
	t->type = type;
	t->after_space = after_space;
	t->expanded = expanded;
	t->next = NULL;
	return (t);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*t;

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
