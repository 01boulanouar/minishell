/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 13:37:55 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_is_valid_quotes(const char *line)
{
	int	squote;
	int	dquote;

	squote = 1;
	dquote = 1;
	while (*line++)
	{
		if (*line == SQUOTE && dquote)
			squote = !squote;
		if (*line == DQUOTE && squote)
			dquote = !dquote;
	}
	return (squote && dquote);
}

int	lex_is_valid_syntax(const char *line)
{
	return (lex_is_valid_quotes(line));
}

int	lex_is_token(char c)
{
	return (c == SQUOTE || c == DQUOTE
		|| c == PIPE || c == LESS
		|| c == GREATER);
}

char	*lex_trim(const char *line)
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

t_token_type	lex_get_token_type(char c)
{
	if (c == SQUOTE)
		return (t_squote);
	else if (c == DQUOTE)
		return (t_dquote);
	else if (c == PIPE)
		return (t_pipe);
	else if (c == LESS)
		return (t_less);
	else if (c == GREATER)
		return (t_greater);
	else
		return (t_unkown);
}
