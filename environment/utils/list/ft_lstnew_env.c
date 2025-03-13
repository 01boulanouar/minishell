/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:51 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:04:52 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *key, char *operator, char *value)
{
	t_env	*t;

	t = ft_malloc_env(sizeof(t_env));
	t->key = key;
	t->value = value;
	t->operator = operator;
	t->next = NULL;
	return (t);
}
