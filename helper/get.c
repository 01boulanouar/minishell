/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:36:18 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 14:39:49 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	get_token_type(const char *value)
{
	if (ft_strlen(value) == 1)
	{
		if (value[0] == DOLLAR)
			return (t_single_dollar);
		if (value[0] == PIPE)
			return (t_pipe);
		else if (value[0] == LESS)
			return (t_less);
		else if (value[0] == GREATER)
			return (t_greater);
	}
	else if (!ft_strncmp(value, DOUBLE_LESS, 2))
		return (t_double_less);
	else if (!ft_strncmp(value, DOUBLE_GREATER, 2))
		return (t_double_greater);
	else
	{
		if (value[0] == DOLLAR)
		{
			if (value[1] && ('0' <= value[1] && value[1] <= '9'))
				return (t_dollar_num);
			else if (value[1])
				return (t_dollar_expand);
		}
		if (value[0] == SINGLE_QUOTE)
			return (t_single_quote);
		else if (value[0] == DOUBLE_QUOTE)
			return (t_double_quote);
	}
	return (t_word);
}
