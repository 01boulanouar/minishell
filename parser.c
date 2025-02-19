/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:33:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/02/19 20:33:09 by aelkadir         ###   ########.fr       */
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

static int	out_files_number(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != t_pipe)
	{
		if (token->type == t_greater || token->type == t_dgreater)
			count++;
		token = token->next;
	}
	return (count);
}

static int	in_files_number(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != t_pipe)
	{
		if (token->type == t_less || token->type == t_dless)
			count++;
		token = token->next;
	}
	return (count);
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

void	handle_redirection(t_comand *cmd, t_token *token, int *in_index,
		int *out_index)
{
	t_token		*next;
	t_redirect	*redir;

	next = token->next;
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return ;
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

t_token	*ft_parse(t_comand *comand, t_token *token)
{
	int	j;
	int	in_index;
	int	out_index;

	j = 0;
	in_index = 0;
	out_index = 0;
	while (token && token->type != t_pipe)
	{
		if (is_redirection(token))
		{
			handle_redirection(comand, token, &in_index, &out_index);
			token = token->next;
		}
		else
		{
			comand->tokens[j++] = token;
		}
		token = token->next;
	}
	comand->tokens[j] = NULL;
	comand->in_files[in_index] = NULL;
	comand->out_files[out_index] = NULL;
	return (token);
}

t_comand	*parse(t_token *token)
{
	int			num_cmds;
	t_comand	*comands;
	int			i;

	i = 0;
	num_cmds = number_of_commands(token);
	comands = malloc(num_cmds * sizeof(t_comand));
	if (!comands)
		return (NULL);
	while (i < num_cmds)
	{
		comands[i].tokens = malloc((n_tokens(token) + 1) * sizeof(t_token *));
		comands[i].in_files = malloc((in_files_number(token) + 1)
				* sizeof(t_redirect *));
		comands[i].out_files = malloc((out_files_number(token) + 1)
				* sizeof(t_redirect *));
		if (!comands[i].tokens || !comands[i].in_files || !comands[i].out_files)
			return (NULL);
		token = ft_parse(&comands[i], token);
		if (token)
			token = token->next;
		i++;
	}
	return (comands);
}
