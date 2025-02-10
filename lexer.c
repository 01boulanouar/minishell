/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 13:47:01 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lex_tokenize(char *line)
{
	t_token	*token;
	int		i;

	token = NULL;
	i = 0;
	while (line[i])
	{
		if (lex_is_token(line[i]))
		{
			ft_lstadd_back(&token, ft_lstnew(line[i],
					lex_get_token_type(line[i])));
		}
		i++;
	}
	return (token);
}

void	lex_print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("token [%c] type [%d]\n", token->value, token->type);
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
