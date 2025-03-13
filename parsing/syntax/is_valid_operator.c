/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:04:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:24:44 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_operator(t_token *token)
{
	int	begining_pipe;

	begining_pipe = 1;
	while (token)
	{
		if (token->type == t_pipe && begining_pipe)
			return (1);
		if (is_operator(token) && (!token->next || is_operator(token->next)))
		{
			if (token->type == t_pipe && token->next
				&& is_redirection(token->next))
				;
			else
				return (1);
		}
		token = token->next;
		begining_pipe = 0;
	}
	return (0);
}
