/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/27 03:15:33 by aelkadir         ###   ########.fr       */
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

int	ft_isvalid_expand(int c)
{
	return (ft_isalnum(c) || c == UNDERSCORE);
}

int	is_dollar_str(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == DOLLAR || str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		i++;
	return (ft_strlen(str) == i);
}
