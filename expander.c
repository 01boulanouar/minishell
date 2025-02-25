/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 18:15:11 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_token(t_token **token, char *name, int after_space)
{
	char			*expanded;
	char			*start;
	char			*value;
	t_token_type	type;

	name++;
	expanded = getenv(name);
	while (expanded && *expanded)
	{
		start = expanded;
		expanded += get_next_token_len(start);
		value = ft_copy(start, expanded);
		type = get_token_type(value);
		ft_lstadd_back_token(token, ft_lstnew_token(value, type, after_space,
				1));
		after_space = ft_isin(*expanded, BLANKS);
		expanded += ft_strspn(expanded, BLANKS);
	}
	return ;
}

int	get_expand_len(char *line)
{
	char	*start;
	char	*expanded;
	int		len;

	len = 0;
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), SEPARATORS))
		{
			start = ++line;
			if (ft_isdigit(*line))
				line++;
			else
				line += ft_strcspn(line, SEPARATORS);
			expanded = getenv(ft_copy(start, line));
			if (expanded)
				len += ft_strlen(expanded);
		}
		else
		{
			line++;
			len++;
		}
	}
	return (len);
}

char	*expand_double_quotes(char *line)
{
	char	*result;
	char	*start;
	char	*expanded;
	char	*result_start;

	result = malloc(get_expand_len(line) + 1);
	result_start = result;
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), SEPARATORS))
		{
			start = ++line;
			if (ft_isdigit(*line))
				line++;
			else
				line += ft_strcspn(line, SEPARATORS);
			expanded = getenv(ft_copy(start, line));
			while (expanded && *expanded)
				*(result++) = *(expanded++);
		}
		else
			*(result++) = *(line++);
	}
	*result = '\0';
	return (result_start);
}
