/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/22 20:08:36 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_expand(t_token **token, char *name, int after_space)
{
	char			*expanded;
	char			*start;
	char			*value;
	t_token_type	type;
	t_token			*new_token;

	if (name[0] != DOLLAR)
		return (0);
	name++;
	expanded = getenv(name);
	if (!expanded)
		return (0);
	while (*expanded)
	{
		start = expanded;
		expanded += lex_get_next_token(start);
		value = ft_copy(start, expanded);
		type = lex_token_type(value);
		new_token = ft_lstnew(value, type, after_space, 1);
		ft_lstadd_back(token, new_token);
		after_space = ft_isin(*expanded, BLANKS);
		expanded += ft_strspn(expanded, BLANKS);
	}
	return (1);
}

char	*lex_expand_dquotes(char *line)
{
	char	*result;
	char	*start;
	char	*name;
	char	*expanded;
	char	*result_start;

	result = malloc(20000);
	result_start = result;
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), SEPARATORS))
		{
			start = ++line;
			line += ft_strcspn(line, SEPARATORS);
			name = ft_copy(start, line);
			expanded = getenv(name);
			while (expanded && *expanded)
				*(result++) = *(expanded++);
		}
		else
			*(result++) = *(line++);
	}
	*result = '\0';
	return (result_start);
}
