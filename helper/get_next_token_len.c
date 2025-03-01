/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:23:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/01 15:08:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_next_quote_token_len(const char *line)
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

size_t	get_next_token_len(const char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strncmp(line, DOUBLE_LESS, 2) || !ft_strncmp(line, DOUBLE_GREATER,
			2) || !ft_strncmp(line, EXIT_STATUS, 2))
		return (2);
	if (line[0] == LESS || line[0] == GREATER || line[0] == PIPE
		|| (line[0] == DOLLAR && !line[1]))
		return (1);
	if (line[0] == SINGLE_QUOTE || line[0] == DOUBLE_QUOTE)
		return (get_next_quote_token_len(line));
	if (line[0] == DOLLAR)
	{
		if (ft_isdigit(line[1]))
			return (2);
		i++;
	}
	if (ft_isvalid(line[i]))
	{
		while (line[i] && !ft_isin(line[i], SEPARATORS) && ft_isvalid(line[i]))
			i++;
	}
	else
	{
		while (line[i] && !ft_isin(line[i], SEPARATORS))
			i++;
	}
	return (i);
}
