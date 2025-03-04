/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:14:43 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/04 17:20:55 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env(char *key, char *operator, char * value)
{
	t_env	*t;

	t = ft_malloc(sizeof(t_env));
	t->key = key;
	t->value = value;
	t->operator= operator;
	t->next = NULL;
	return (t);
}

t_env	*ft_lstnew_env_from_str(char *str)
{
	char	*start;
	char	*key;
	char	*operator;
	char	*value;

	start = str;
	while (*str)
	{
		if (*str == EQUAL || (*str == PLUS && (*(str + 1) && *(str
						+ 1) == EQUAL)))
			break ;
		str++;
	}
	key = ft_copy(start, str);
	start = str;
	if (*str == PLUS && (*(str + 1) && *(str + 1) == EQUAL))
		str++;
	if (*str == EQUAL)
		str++;
	operator= ft_copy(start, str);
	start = str;
	while (*str)
		str++;
	value = ft_copy(start, str);
	return (ft_lstnew_env(key, operator, value));
}

void	ft_lstadd_back_env(t_env *new)
{
	t_env	*t;
	t_env	**lst;

	lst = get_env_head();
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

void	ft_lstremove_env(char *key)
{
	t_env	**env;

	env = get_env_head();
	if (!env || !(*env))
		return ;
	while (*env)
	{
		if (!ft_strcmp(key, (*env)->key))
			*env = (*env)->next;
		else
			env = &(*env)->next;
	}
}

int	ft_lstsize(t_env *env)
{
	size_t	size;

	if (!env)
		return (0);
	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
