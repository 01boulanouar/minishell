/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:47:29 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/28 17:50:46 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lst_swap_env(t_env *node, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_operator;

	tmp_key = node->key;
	tmp_value = node->value;
	tmp_operator = node->operator;
	node->key = next->key;
	node->value = next->value;
	node->operator = next->operator;
	next->key = tmp_key;
	next->value = tmp_value;
	next->operator = tmp_operator;
	return (1);
}

static void	ft_lstadd_back_copy_env(t_env **lst, t_env *new)
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

void	ft_lstfree_copy_env(t_env **env)
{
	t_env	*node;
	t_env	*tmp;

	if (!env || !*env)
		return ;
	node = *env;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp->operator);
		free(tmp);
	}
	*env = NULL;
}

static t_env	*ft_lstcopy_env(void)
{
	t_env	**env;
	t_env	*env_copy;
	t_env	*node;
	t_env	*new;

	env = get_env_head();
	if (!env)
		return (NULL);
	env_copy = NULL;
	node = *env;
	while (node)
	{
		new = ft_lstnew_env(node->key, node->operator, node->value);
		ft_lstadd_back_copy_env(&env_copy, new);
		node = node->next;
	}
	return (env_copy);
}

t_env	*sort_env(void)
{
	int		swapped;
	t_env	*env;
	t_env	*node;
	t_env	*tmp;

	env = ft_lstcopy_env();
	if (!env)
		return (NULL);
	swapped = 1;
	tmp = NULL;
	while (swapped)
	{
		swapped = 0;
		node = env;
		while (node->next != tmp)
		{
			if (ft_strcmp(node->key, node->next->key) > 0)
				swapped = ft_lst_swap_env(node, node->next);
			node = node->next;
		}
		tmp = node;
	}
	return (env);
}
