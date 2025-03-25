/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 02:47:52 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token *token)
{
	return ((token->type == t_less || token->type == t_greater
			|| token->type == t_double_less
			|| token->type == t_double_greater));
}

int	is_pipe(t_token *token)
{
	return (token->type == t_pipe);
}

int	is_quotes(t_token *token)
{
	return (token->type == t_single_quote
		|| token->type == t_double_quote);
}

int	is_operator(t_token *token)
{
	return (is_redirection(token) || is_pipe(token));
}

int	get_number_of_arguments(t_command command)
{
	int	i;

	if (!command.tokens || !command.tokens[0])
		return (0);
	i = 1;
	while (command.tokens[i])
		i++;
	return (i - 1);
}
