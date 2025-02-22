/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:33 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/22 15:56:37 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_print_token_type(t_token_type type)
{
	if (type == t_pipe)
		return ("PIPE");
	else if (type == t_dollar)
		return ("DOLLAR");
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

void	lex_print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("[%s] %s space %d expanded %d\n", token->value,
			lex_print_token_type(token->type), token->after_space,
			token->expanded);
		token = token->next;
	}
}
