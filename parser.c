/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:33:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/02/25 14:27:04 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(t_comand *cmd, t_token *token, int *in_index,
		int *out_index)
{
	t_token		*next;
	t_redirect	*redir;

	next = token->next;
	redir = ft_malloc(sizeof(t_redirect));
	redir->file = next->value;
	if (token->type == t_greater)
		redir->type = ">";
	if (token->type == t_less)
		redir->type = "<";
	if (token->type == t_double_greater)
		redir->type = ">>";
	if (token->type == t_double_less)
		redir->type = "<<";
	if (token->type == t_greater || token->type == t_double_greater)
		cmd->out_files[(*out_index)++] = redir;
	else
		cmd->in_files[(*in_index)++] = redir;
}

t_token	*parse_token(t_comand *comand, t_token *token)
{
	int	j;
	int	in_index;
	int	out_index;

	j = 0;
	in_index = 0;
	out_index = 0;
	while (token)
	{
		if (token->type == t_pipe && !token->expanded)
			break ;
		if (is_redirection(token))
		{
			if (token->next && token->next->next && token->next->expanded
				&& token->next->next->expanded)
				comand->not_to_be_executed = 1;
			handle_redirection(comand, token, &in_index, &out_index);
			token = token->next;
		}
		else
			comand->tokens[j++] = token;
		token = token->next;
	}
	return (comand->tokens[j] = NULL, comand->in_files[in_index] = NULL,
		comand->out_files[out_index] = NULL, token);
}

t_comand	*parser(t_token *token)
{
	int			num_cmds;
	t_comand	*comands;
	int			i;

	i = 0;
	num_cmds = get_number_of_commands(token);
	comands = ft_malloc(num_cmds * sizeof(t_comand));
	while (i < num_cmds)
	{
		comands[i].tokens = ft_malloc((get_number_of_tokens(token) + 1)
				* sizeof(t_token *));
		comands[i].in_files = ft_malloc((get_number_of_infiles(token) + 1)
				* sizeof(t_redirect *));
		comands[i].out_files = ft_malloc((get_number_of_outfiles(token) + 1)
				* sizeof(t_redirect *));
		if (!comands[i].tokens || !comands[i].in_files || !comands[i].out_files)
			return (NULL);
		token = parse_token(&comands[i], token);
		if (token)
			token = token->next;
		i++;
	}
	return (comands);
}
