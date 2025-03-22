/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:22:32 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 01:47:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_token(t_token **token)
{
	t_token	*current;
	t_token	*next_token;

	current = *token;
	while (current && current->next)
	{
		next_token = current->next;
		if (next_token && !current->has_space && !is_operator(current)
			&& !is_operator(next_token))
		{
			if (current->next->type == t_double_quote
				|| current->next->type == t_single_quote)
				current->type = current->next->type;
			current->value = ft_strjoin(current->value, next_token->value);
			current->next = next_token->next;
			current->has_space = next_token->has_space;
		}
		else
			current = current->next;
	}
}
