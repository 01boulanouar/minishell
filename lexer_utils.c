/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/09 16:57:34 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_quotes(char *line)
{
	int	i;
	int	closed_squote;
	int	closed_dquote;

	closed_squote = 1;
	closed_dquote = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == SQUOTE && closed_dquote)
			closed_squote = !closed_squote;
		if (line[i] == DQUOTE && closed_squote)
			closed_dquote = !closed_dquote;
		i++;
	}
	return (closed_squote && closed_dquote);
}

int	is_valid_syntax(char *line)
{
	return (is_valid_quotes(line));
}
