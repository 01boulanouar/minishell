/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:24:34 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 17:32:24 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_quotes(const char *line)
{
	int	squote;
	int	dquote;

	squote = 1;
	dquote = 1;
	while (line && *line)
	{
		if (*line == SINGLE_QUOTE && dquote)
			squote = !squote;
		if (*line == DOUBLE_QUOTE && squote)
			dquote = !dquote;
		line++;
	}
	return (squote && dquote);
}
