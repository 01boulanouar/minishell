/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/14 16:51:47 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lex_skip_quotes(const char *line)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (line[i] == SQUOTE)
		quote = SQUOTE;
	else if (line[i] == DQUOTE)
		quote = DQUOTE;
	if (quote)
	{
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] == quote)
			i++;
	}
	else
	{
		while (line[i] && !ft_isin(line[i], SEPARATORS))
			i++;
	}
	return (i);
}

t_token	*lex_tokenize(char *line)
{
	const char		*start;
	t_token			*token;
	char			*value;
	t_token_type	type;
	int				token_after_space;

	token_after_space = 0;
	while (*line)
	{
		start = line;
		if ((*line == LESS || *line == GREATER))
			line++;
		else
			line += lex_skip_quotes(line);
		if (((*line == LESS || *line == GREATER) && *line == *start))
			line++;
		value = ft_copy(start, line);
		if (!value)
			return (token);
		type = lex_get_token_type(value);
		ft_lstadd_back(&token, ft_lstnew(value, type, token_after_space));
		token_after_space = ft_isin(*line, BLANKS);
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

void	lex_print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("[%s] %s %d\n", token->value, lex_print_token_type(token->type),
			token->token_after_space);
		token = token->next;
	}
}

void	lexer(char *line)
{
	t_token	*token;
	char	*trim_line;

	token = NULL;
	if (!lex_is_valid_syntax(line))
	{
		ft_putstr_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	trim_line = lex_trim(line);
	free(line);
	line = NULL;
	token = lex_tokenize(trim_line);
	free(trim_line);
	trim_line = NULL;
	lex_print_tokens(token);
	ft_lstfree(&token);
}
