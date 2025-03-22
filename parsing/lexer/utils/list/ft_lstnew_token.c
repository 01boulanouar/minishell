/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:21:34 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 01:47:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(char *value, t_token_type type, int has_space)
{
	t_token	*t;

	t = ft_malloc(sizeof(t_token));
	if (type == t_single_quote || type == t_double_quote)
		value = ft_copy(value + 1, value + ft_strlen(value) - 1);
	t->value = value;
	t->type = type;
	t->has_space = has_space;
	t->next = NULL;
	return (t);
}
