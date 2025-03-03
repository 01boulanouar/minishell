/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:04:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/03 01:03:54 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_quotes(const char *line)
{
	int	squote;
	int	dquote;

	squote = 1;
	dquote = 1;
	while (line && *line)
	{
		if (*line == SINGLE_QUOTE && dquote)
			squote = !squote;
		if (*line == DOUBLE_QUOTE && squote)
			dquote = !dquote;
		line++;
	}
	return (squote && dquote);
}

int	operator_error(t_token *token)
{
	int	begining_pipe;

	begining_pipe = 1;
	while (token)
	{
		if (token->type == t_pipe && begining_pipe)
			return (1);
		if (is_operator(token) && (!token->next || is_operator(token->next)))
		{
			if(token->type==t_pipe && token->next && is_redirection(token->next))
				;  
			else
				return 1 ; 
		}
		token = token->next;
		begining_pipe = 0;
	}
	return (0);
}
