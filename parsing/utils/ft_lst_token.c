/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:36:47 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 23:00:14 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*ft_lstnew_token(char *value, t_token_type type, int after_space)
{
	t_token	*t;

	t = ft_malloc(sizeof(t_token));
	if (type == t_single_quote || type == t_double_quote)
		value = ft_copy(value + 1, value + ft_strlen(value) - 1);
	t->value = value;
	t->type = type;
	t->after_space = after_space;
	t->next = NULL;
	return (t);
}

int	get_number_of_arguments(t_command command)
{
	int	i;

	if (!command.tokens || !command.tokens[0])
		return (0);
	i = 1;
	while (command.tokens[i])
		i++;
	return (i - 1);
}
