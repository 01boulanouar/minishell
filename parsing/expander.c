/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/11 20:30:25 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_expand_len_if(char **line, int *len)
{
	char	*expanded;
	char	*start;

	expanded = NULL;
	start = ++(*line);
	if (ft_isdigit(**line))
		(*line)++;
	else if (**line == '?')
	{
		(*line)++;
		expanded = ft_itoa(*ft_get_exit_status());
	}
	else
	{
		while (ft_isvalid_expand(**line))
			(*line)++;
		expanded = ft_getenv(ft_copy(start, *line));
	}
	if (expanded)
		*len += ft_strlen(expanded);
}

static int	get_expand_len(char *line)
{
	int	len;

	len = 0;
	if (!line)
		return (0);
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), D_SEP))
			get_expand_len_if(&line, &len);
		else
		{
			line++;
			len++;
		}
	}
	return (len);
}

static void	expand_str_if(char **line, char **result)
{
	char	*start;
	char	*expanded;

	expanded = NULL;
	start = ++(*line);
	if (ft_isdigit(**line))
		(*line)++;
	else if (**line == '?')
	{
		(*line)++;
		expanded = ft_itoa(*ft_get_exit_status());
	}
	else
	{
		while (ft_isvalid_expand(**line))
			(*line)++;
		expanded = ft_getenv(ft_copy(start, *line));
	}
	while (expanded && *expanded)
		*((*result)++) = *(expanded++);
}

char	*expand_str(char *line)
{
	char	*result;
	char	*result_start;

	result = ft_malloc(get_expand_len(line) + 1);
	result_start = result;
	if (!line)
		return (NULL);
	if (is_dollar_str(line))
		return (line);
	while (*line)
	{
		if (*line == DOLLAR && *(line + 1) && !ft_isin(*(line + 1), D_SEP))
			expand_str_if(&line, &result);
		else
			*(result++) = *(line++);
	}
	*result = '\0';
	return (result_start);
}

int	expand_token(t_token **token, char *name, int a_s)
{
	char	*expanded;
	char	*start;
	char	*value;
	if (!ft_strncmp(name, EXIT_STATUS, 2))
		expanded = ft_itoa(*ft_get_exit_status());
	else
		expanded = ft_getenv(++name);
	if (!expanded)
		return (0);
	if (ft_isallspace(expanded))
		return (1);
	while (expanded && *expanded)
	{
		expanded += ft_strspn(expanded, BLANKS);
		start = expanded;
		expanded += get_next_token_len(start);
		value = ft_copy(start, expanded);
		ft_lstadd_back_token(token, ft_lstnew_token(value, t_expanded, a_s));
		a_s = ft_isin(*expanded, BLANKS);
		expanded += ft_strspn(expanded, BLANKS);
	}
	return (0);
}
