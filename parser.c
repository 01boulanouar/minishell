/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:03:11 by aelkadir          #+#    #+#             */
/*   Updated: 2025/02/16 17:03:12 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_token *token)
{
	return (token->type == t_less || token->type == t_greater
		|| token->type == t_dless || token->type == t_dgreater);
}

int	number_of_commands(t_token *token)
{
	int	counter;

	counter = 1;
	while (token)
	{
		if (token->type == t_pipe)
			counter++;
		token = token->next;
	}
	return (counter);
}

static int	n_tokens(t_token *token)
{
	int	count;
	int	redirections;

	count = 0;
	redirections = 0;
	while (token && token->type != t_pipe)
	{
		count++;
		if (is_redirection(token))
			redirections++;
		token = token->next;
	}
	return (count - (2 * redirections));
}

t_comand	*parse(t_token *token)
{
	t_comand	*comands;
	int			i;
	int			j;

	comands = malloc(number_of_commands(token) * sizeof(t_comand));
	i = -1;
	while (comands && token && number_of_commands(token) > 0)
	{
		comands[++i].tokens = malloc((n_tokens(token) + 1) * sizeof(t_token *));
		if (!comands[i].tokens)
			return (NULL);
		j = 0;
		while (token && token->type != t_pipe)
		{
			if (is_redirection(token))
				token = token->next;
			else
				comands[i].tokens[j++] = token;
			token = token->next;
		}
		comands[i].tokens[j] = NULL;
		if (token)
			token = token->next;
	}
	return (comands);
}
