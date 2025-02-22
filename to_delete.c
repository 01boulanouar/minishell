/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:33 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/22 21:19:50 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_print_token_type(t_token_type type)
{
	if (type == t_pipe)
		return ("PIPE");
	else if (type == t_dollar)
		return ("DOLLAR");
	else if (type == t_dollar_num)
		return ("DOLLAR NUM");
	else if (type == t_dollar_expand)
		return ("DOLLAR EXPAND");
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
