/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:36:18 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:03:34 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_operator_type(const char *value)
{
	if (*value == PIPE)
		return (t_pipe);
	else if (*value == LESS)
		return (t_less);
	else if (*value == GREATER)
		return (t_greater);
	if (*value == DOLLAR)
		return (t_single_dollar);
	return (t_word);
}

static t_token_type	get_dollar_type(const char *value)
{
	if (ft_isdigit(value[1]))
		return (t_dollar_num);
	else if (!ft_strncmp(value, EXIT_STATUS, 2))
		return (t_exit_status);
	else
		return (t_dollar_expand);
}

static t_token_type	get_quotes_type(const char *value)
{
	if (*value == SINGLE_QUOTE)
		return (t_single_quote);
	else if (*value == DOUBLE_QUOTE)
		return (t_double_quote);
	return (t_word);
}

static t_token_type	get_redirection_type(const char *value)
{
	if (!ft_strncmp(value, DOUBLE_LESS, 2))
		return (t_double_less);
	else if (!ft_strncmp(value, DOUBLE_GREATER, 2))
		return (t_double_greater);
	return (get_quotes_type(value));
}

t_token_type	get_token_type(const char *value)
{
	if (ft_strlen(value) == 1)
		return (get_operator_type(value));
	else if (*value == DOLLAR)
		return (get_dollar_type(value));
	else if (ft_strlen(value) == 2)
		return (get_redirection_type(value));
	else
		return (get_quotes_type(value));
	return (t_word);
}
