/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/14 16:34:36 by moboulan         ###   ########.fr       */
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
	return (lex_is_valid_quotes(line));
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

t_token_type	lex_get_token_type(const char *value)
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
	if (type == t_dless)
		return ("DOUBLE LESS");
	else if (type == t_dgreater)
		return ("DOUBLE GREATER");
	else if (type == t_pipe)
		return ("PIPE");
	else if (type == t_less)
		return ("LESS");
	else if (type == t_greater)
		return ("GREATER");
	else if (type == t_squote)
		return ("SINGLE_QUOTES");
	else if (type == t_dquote)
		return ("DOUBLE_QUOTES");
	else if (type == t_word)
		return ("WORD");
	else
		return ("UNKOWN");
}
