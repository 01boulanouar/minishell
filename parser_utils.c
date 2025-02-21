/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:58:30 by aelkadir          #+#    #+#             */
/*   Updated: 2025/02/20 15:58:32 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token *token)
{
	return (!token->expanded && (token->type == t_less
			|| token->type == t_greater || token->type == t_dless
			|| token->type == t_dgreater));
}

int	number_of_commands(t_token *token)
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

int	out_files_number(t_token *token)
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

int	in_files_number(t_token *token)
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

int	n_tokens(t_token *token)
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
		if (is_redirection(token))
			redirections++;
		token = token->next;
	}
	return (count - (2 * redirections));
}

void	handle_redirection(t_comand *cmd, t_token *token, int *in_index,
		int *out_index)
{
	t_token *next;
	t_redirect *redir;

	next = token->next;
	redir = ft_malloc(sizeof(t_redirect));
	redir->file = next->value;
	if (token->type == t_greater)
		redir->type = ">";
	if (token->type == t_less)
		redir->type = "<";
	if (token->type == t_dgreater)
		redir->type = ">>";
	if (token->type == t_dless)
		redir->type = "<<";
	if (token->type == t_greater || token->type == t_dgreater)
		cmd->out_files[(*out_index)++] = redir;
	else
		cmd->in_files[(*in_index)++] = redir;
}