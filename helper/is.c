/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 15:43:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_token *token)
{
	return (!token->expanded && (token->type == t_less
			|| token->type == t_greater || token->type == t_double_less
			|| token->type == t_double_greater));
}

int	is_pipe(t_token *token)
{
	return ((!token->expanded && token->type == t_pipe));
}

int	is_operator(t_token *token)
{
	return (is_redirection(token) || is_pipe(token));
}
