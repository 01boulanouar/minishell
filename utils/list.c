/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:14:43 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 17:33:27 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(char *value, t_token_type type, int token_after_space)
{
	t_token	*t;

	t = ft_malloc(sizeof(t_token));
	t->value = value;
	t->type = type;
	t->token_after_space = token_after_space;
	t->next = NULL;
	return (t);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*t;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast(*lst);
		t->next = new;
	}
}
