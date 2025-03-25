/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:58:36 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/25 05:44:33 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isin_env(char *key)
{
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	while (node)
	{
		if (node->key && !ft_strcmp(node->key, key))
			return (1);
		node = node->next;
	}
	return (0);
}

int	ft_isvalid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != UNDERSCORE)
		return (0);
	while (ft_isalnum(key[i]) || key[i] == UNDERSCORE)
		i++;
	return (ft_strlen(key) == i);
}

t_gc	**ft_gc_env(void)
{
	static t_gc	*head;

	return (&head);
}

void	*ft_malloc_env(size_t size)
{
	t_gc	**head;
	t_gc	*new_node;
	void	*ptr;

	head = ft_gc_env();
	ptr = malloc(size);
	if (!ptr)
		ft_exit(EXIT_FAILURE);
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		ft_exit(EXIT_FAILURE);
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
	return (ptr);
}

void	ft_free_env(void)
{
	t_gc	**head;
	t_gc	*curr;
	t_gc	*tmp;

	head = NULL;
	head = ft_gc_env();
	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->ptr);
		free(tmp);
	}
	*head = NULL;
}
