/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/20 17:00:27 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lex_get_next_quote(const char *line)
{
	size_t	i;
	char	quote;
	
	i = 0;
	quote = '\0';
	if (line[0] == SQUOTE)
		quote = SQUOTE;
	else if (line[0] == DQUOTE)
		quote = DQUOTE;
	if (quote)
	{
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] == quote)
			i++;
	}
	return (i);
}

size_t	lex_get_next_token(const char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strncmp(line, DLESS, 2) || !ft_strncmp(line, DGREATER, 2))
		return (2);
	else if (line[0] == LESS || line[0] == GREATER || line[0] == PIPE)
		return (1);
	else if (line[0] == SQUOTE || line[0] == DQUOTE)
		return (lex_get_next_quote(line));
	else
	{
		if (line[0] == DOLLAR)
			i++;
		while (line[i] && !ft_isin(line[i], SEPARATORS))
			i++;
	}
	return (i);
}

t_token	*lex_tokenize(char *line)
{
	const char	*start;
	t_token		*token;
	char		*value;
	char		*expanded;
	t_token_type type;
	int			after_space;

	token = NULL;
	after_space = 0;
	while (*line)
	{
		start = line;
		line += lex_get_next_token(line);
		value = ft_copy(start, line);
		type = lex_t_type(value);
		if (type == t_dollar)
		{
			char *expanded_start;
			char *expanded_value;
			expanded = getenv(++value);
			while(expanded && *expanded)
			{
				expanded_start = expanded;
				expanded += lex_get_next_token(expanded_start);
				expanded_value = ft_copy(expanded_start, expanded);
				ft_lstadd_back(&token, ft_lstnew(expanded_value, lex_t_type(expanded_value), after_space, 1));
				after_space = ft_isin(*expanded, BLANKS);
				expanded += ft_strspn(expanded, BLANKS);
			}
			value--;
		}
		if(type != t_dollar || !expanded)
		{
			ft_lstadd_back(&token, ft_lstnew(value, type , after_space, 0));
			after_space = ft_isin(*line, BLANKS);
		}
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

char	*lex_trim(char *line)
{
	const char	*start;
	const char	*end;

	start = line;
	end = line + ft_strlen(line);
	while (*start && ft_isin(*start, BLANKS))
		start++;
	while (end >= start && ft_isin(*end, BLANKS))
		end--;
	return (ft_copy(start, end));
}

void	lex_print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("[%s] %s space %d expanded %d\n", token->value, lex_print_token_type(token->type),
			token->after_space, token->expanded);
		token = token->next;
	}
}

t_token	*lexer(char *line)
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
	token = lex_tokenize(trim_line);
	if (operator_error(token))
	{
		ft_putstr_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	return (token);
}
