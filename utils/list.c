/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:14:43 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 18:41:35 by moboulan         ###   ########.fr       */
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

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*t;

	t = ft_malloc(sizeof(t_env));
	t->key = key;
	t->value = value;
	t->next = NULL;
	return (t);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
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
