/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:23:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/18 16:49:35 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_next_quote_token_len(const char *line)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (line[0] == SINGLE_QUOTE)
		quote = SINGLE_QUOTE;
	else if (line[0] == DOUBLE_QUOTE)
		quote = DOUBLE_QUOTE;
	if (quote)
	{
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] == quote)
			i++;
	}
	return (i);
}

static size_t	is_redirection_str(const char *line)
{
	return (!ft_strncmp(line, DOUBLE_LESS, 2)
		|| !ft_strncmp(line, DOUBLE_GREATER, 2));
}

static size_t	is_operator_str(const char *line)
{
	return (line[0] == LESS || line[0] == GREATER
		|| line[0] == PIPE || (line[0] == DOLLAR && !line[1]));
}

static size_t	is_exit_status_str(const char *line)
{
	return (!ft_strncmp(line, EXIT_STATUS, 2)
		|| (line[0] == DOLLAR && ft_isdigit(line[1])));
}

size_t	get_next_token_len(const char *line)
{
	size_t	i;

	i = 0;
	if (is_redirection_str(line) || is_exit_status_str(line))
		return (2);
	if (is_operator_str(line))
		return (1);
	if (line[0] == SINGLE_QUOTE || line[0] == DOUBLE_QUOTE)
		return (get_next_quote_token_len(line));
	if (line[0] == DOLLAR)
		i++;
	while (line[i] && !ft_isin(line[i], SEPARATORS))
			i++;
	return (i);
}
