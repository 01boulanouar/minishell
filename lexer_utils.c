/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/22 15:56:25 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_is_valid_quotes(const char *line)
{
	int	squote;
	int	dquote;

	squote = 1;
	dquote = 1;
	while (*line)
	{
		if (*line == SQUOTE && dquote)
			squote = !squote;
		if (*line == DQUOTE && squote)
			dquote = !dquote;
		line++;
	}
	return (squote && dquote);
}

int	lex_is_valid_syntax(const char *line)
{
	return (lex_is_valid_quotes(line) && lex_is_valid_pipes(line));
}

int	is_operator(t_token *token)
{
	return (!token->expanded && (token->type == t_less
			|| token->type == t_greater || token->type == t_dless
			|| token->type == t_dgreater || token->type == t_pipe));
}

int	operator_error(t_token *token)
{
	while (token)
	{
		if (is_operator(token) && (!token->next || is_operator(token->next)))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token_type	lex_token_type(const char *value)
{
	if (value[0] == DOLLAR)
		return (t_dollar);
	if (ft_strlen(value) == 1)
	{
		if (value[0] == PIPE)
			return (t_pipe);
		else if (value[0] == LESS)
			return (t_less);
		else if (value[0] == GREATER)
			return (t_greater);
	}
	else if (!ft_strcmp(value, DLESS))
		return (t_dless);
	else if (!ft_strcmp(value, DGREATER))
		return (t_dgreater);
	else
	{
		if (value[0] == SQUOTE)
			return (t_squote);
		else if (value[0] == DQUOTE)
			return (t_dquote);
	}
	return (t_word);
}
