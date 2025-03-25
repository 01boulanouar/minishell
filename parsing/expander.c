/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 02:52:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalid_expand(int c)
{
	return (ft_isalnum(c) || c == UNDERSCORE);
}

static int	get_expand_len(char *line)
{
	char	*start;
	char	*expanded;
	int		len;

	len = 0;
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), D_SEPARATORS))
		{
			start = ++line;
			if (ft_isdigit(*line))
				line++;
			else if (*line == '?')
			{
				line++;
				expanded = ft_itoa(*ft_get_exit_status());
			}
			else 
			{
				line += ft_strcspn(line, " 	\'\"<>|");
				expanded = ft_getenv(ft_copy(start, line));
			}
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

char	*expand_str(char *line)
{
	char	*result;
	char	*start;
	char	*expanded;
	char	*result_start;

	result = ft_malloc(get_expand_len(line) + 1);
	result_start = result;
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), D_SEPARATORS))
		{
			start = ++line;
			if (ft_isdigit(*line))
				line++;
			else if (*line == '?')
			{
				line++;
				expanded = ft_itoa(*ft_get_exit_status());	
			}
			else
			{
				line += ft_strcspn(line, D_SEPARATORS);
				expanded = ft_getenv(ft_copy(start, line));
			}
			while (expanded && *expanded)
				*(result++) = *(expanded++);
		}
		else
			*(result++) = *(line++);
	}
	*result = '\0';
	return (result_start);
}


void	expand_token(t_token **token, char *name, int after_space)
{
	char			*expanded;
	char			*start;
	char			*value;

	if (!strncmp(name, EXIT_STATUS, 2))
		expanded = ft_itoa(*ft_get_exit_status());
	else
	{
		name++;
		expanded = ft_getenv(name);
	}
	if (!expanded)
	{
		value = ft_strdup("");
		ft_lstadd_back_token(token, ft_lstnew_token(value, t_expanded, after_space));
		return ;
	}
	while (expanded && *expanded)
	{
		start = expanded;
		expanded += get_next_token_len(start);
		value = ft_copy(start, expanded);
		ft_lstadd_back_token(token, ft_lstnew_token(value, t_expanded, after_space));
		after_space = ft_isin(*expanded, BLANKS);
		expanded += ft_strspn(expanded, BLANKS);
	}
	return ;
}
