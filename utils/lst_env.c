/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:14:43 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 10:37:04 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*t;

	t = malloc(sizeof(t_env));
	if (!t)
		return (NULL);
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

void	ft_lstremove_env(t_env **env, char *key)
{
	t_env	*tmp;

	if (!env || !(*env))
		return ;
	if (!ft_strcmp(key, (*env)->key))
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
		ft_lstremove_env(env, key);
	}
	else
		ft_lstremove_env(&(*env)->next, key);
}

void	ft_lstfree_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		(*env) = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	tmp = NULL;
}
