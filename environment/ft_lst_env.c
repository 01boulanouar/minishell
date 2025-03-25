/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:30 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 02:44:42 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env *new)
{
	t_env	*t;
	t_env	**lst;

	lst = get_env_list();
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

t_env	*ft_lstnew_env_from_str(char *str)
{
	char	*start;
	char	*key;
	char	*operator;
	char	*value;

	start = str;
	while (*str)
	{
		if (*str == EQUAL || !ft_strncmp(str, "+=", 2))
			break ;
		str++;
	}
	key = ft_copy_env(start, str);
	start = str;
	if (!ft_strncmp(str, "+=", 2))
		str++;
	if (*str == EQUAL)
		str++;
	operator = ft_copy_env(start, str);
	start = str;
	while (*str)
		str++;
	value = ft_copy_env(start, str);
	return (ft_lstnew_env(key, operator, value));
}


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

void	ft_lstremove_env(char *key)
{
	t_env	**env;

	env = get_env_list();
	if (!env || !(*env))
		return ;
	while (*env)
	{
		if (!ft_strcmp(key, (*env)->key))
		{
			*env = (*env)->next;
			break ;
		}
		else
			env = &(*env)->next;
	}
}

int	ft_lstsize_env(t_env *env)
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
