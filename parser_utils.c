/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:58:30 by aelkadir          #+#    #+#             */
/*   Updated: 2025/02/22 15:54:31 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_is_redirection(t_token *token)
{
	return (!token->expanded && (token->type == t_less
			|| token->type == t_greater || token->type == t_dless
			|| token->type == t_dgreater));
}

int	parse_number_of_commands(t_token *token)
{
	int	counter;

	counter = 1;
	while (token)
	{
		if (token->type == t_pipe && !token->expanded)
			counter++;
		token = token->next;
	}
	return (counter);
}

int	parse_out_files_number(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == t_pipe && !token->expanded)
			break ;
		if (!token->expanded && (token->type == t_greater
				|| token->type == t_dgreater))
			count++;
		token = token->next;
	}
	return (count);
}

int	parse_in_files_number(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == t_pipe && !token->expanded)
			break ;
		if (!token->expanded && (token->type == t_less
				|| token->type == t_dless))
			count++;
		token = token->next;
	}
	return (count);
}

int	parse_n_tokens(t_token *token)
{
	int	count;
	int	redirections;

	count = 0;
	redirections = 0;
	while (token)
	{
		if (token->type == t_pipe && !token->expanded)
			break ;
		count++;
		if (parse_is_redirection(token))
			redirections++;
		token = token->next;
	}
	return (count - (2 * redirections));
}
