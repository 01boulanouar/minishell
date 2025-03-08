/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/06 21:10:36 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			expanded = ft_getenv(ft_copy(start, line));
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

	result = ft_malloc(get_expand_len(line) + 1);
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
			expanded = ft_getenv(ft_copy(start, line));
			while (expanded && *expanded)
				*(result++) = *(expanded++);
		}
		else
			*(result++) = *(line++);
	}
	*result = '\0';
	return (result_start);
}
