/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 15:18:56 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lex_skip_quotes(const char *line)
{
	size_t	i;
	char	quote;

	quote = '\0';
	i = ft_strcspn(line, QUOTES);
	if (line[i] == SQUOTE)
		quote = SQUOTE;
	else if (line[i] == DQUOTE)
		quote = DQUOTE;
	if (line[i] == quote)
	{
		i++;
		while (line[i] && line[i] != quote)
			i++;
		i++;
	}
	return (i);
}

t_token	*lex_tokenize(char *line)
{
	t_token			*token;
	const char		*start;
	char			*value;
	t_token_type	type;

	token = NULL;
	while (line < line + ft_strlen(line))
	{
		start = line;
		line += lex_skip_quotes(line);
		line += ft_strcspn(line, BLANKS);
		value = ft_copy(start, line);
		type = lex_get_token_type(value);
		ft_lstadd_back(&token, ft_lstnew(value, type));
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
		printf("token [%s] type [%d]\n", token->value, token->type);
		token = token->next;
	}
}

void	lexer(char *line)
{
	t_token	*token;

	if (!lex_is_valid_syntax(line))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n",
			STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	line = lex_trim(line);
	token = lex_tokenize(line);
	lex_print_tokens(token);
}
