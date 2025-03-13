/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_of.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:15 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:03:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_number_of_tokens(t_token *token)
{
	int	count;
	int	redirections;

	count = 0;
	redirections = 0;
	while (token)
	{
		if (token->type == t_pipe)
			break ;
		count++;
		if (is_redirection(token))
			redirections++;
		token = token->next;
	}
	return (count - (2 * redirections));
}

int	get_number_of_commands(t_token *token)
{
	int	count;

	count = 1;
	while (token)
	{
		if (token->type == t_pipe)
			count++;
		token = token->next;
	}
	return (count);
}

int	get_number_of_infiles(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == t_pipe)
			break ;
		if ((token->type == t_less || token->type == t_double_less))
			count++;
		token = token->next;
	}
	return (count);
}

int	get_number_of_outfiles(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == t_pipe)
			break ;
		if ((token->type == t_greater || token->type == t_double_greater))
			count++;
		token = token->next;
	}
	return (count);
}

int	get_number_of_herdocs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == t_double_less)
			count++;
		token = token->next;
	}
	return (count);
}
