/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/17 17:41:40 by moboulan         ###   ########.fr       */
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

int	lex_is_valid_pipes(const char *line)
{
	int		pipe;
	char	quote;

	pipe = 1;
	while (*line)
	{
		quote = '\0';
		if (*line == SQUOTE)
			quote = SQUOTE;
		else if (*line == DQUOTE)
			quote = DQUOTE;
		if (quote)
		{
			line++;
			while (*line && *line != quote)
				line++;
			if (*line == quote)
				line++;
		}
		if (*line == PIPE && *(line + 1 + ft_skip_blanks(line + 1)) == PIPE)
			pipe = 0;
		line++;
	}
	return (pipe);
}

int	lex_is_valid_syntax(const char *line)
{
	return (lex_is_valid_quotes(line) && lex_is_valid_pipes(line));
}

int	operator_error(t_token *token)
{
	while (token)
	{
		if (token->type != t_word && (!token->next
				|| token->next->type != t_word))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token_type	lex_t_type(const char *value)
{
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

char	*lex_print_token_type(t_token_type type)
{
	if (type == t_pipe)
		return ("PIPE");
	else if (type == t_less)
		return ("LESS");
	else if (type == t_greater)
		return ("GREATER");
	else if (type == t_dless)
		return ("DOUBLE LESS");
	else if (type == t_dgreater)
		return ("DOUBLE GREATER");
	else if (type == t_squote)
		return ("SINGLE_QUOTES");
	else if (type == t_dquote)
		return ("DOUBLE_QUOTES");
	else if (type == t_word)
		return ("WORD");
	else
		return ("UNKOWN");
}
