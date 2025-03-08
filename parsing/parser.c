/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:33:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/06 21:10:42 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection(t_command *cmd, t_token *token, int *in_index,
		int *out_index)
{
	t_token		*next;
	t_redirect	*redir;

	next = token->next;
	redir = ft_malloc(sizeof(t_redirect));
	redir->file = next->value;
	redir->type = token->type;
	if (token->type == t_greater || token->type == t_double_greater)
		cmd->out_files[(*out_index)++] = redir;
	else
		cmd->in_files[(*in_index)++] = redir;
}

t_token	*parse_token(t_command *command, t_token *token)
{
	int	j;
	int	in_index;
	int	out_index;

	j = 0;
	in_index = 0;
	out_index = 0;
	while (token)
	{
		if (token->type == t_pipe)
			break ;
		if (is_redirection(token))
		{
			if (token->next && token->next->next)
				command->not_to_be_executed = 1;
			handle_redirection(command, token, &in_index, &out_index);
			token = token->next;
		}
		else
			command->tokens[j++] = token;
		token = token->next;
	}
	return (command->tokens[j] = NULL, command->in_files[in_index] = NULL,
		command->out_files[out_index] = NULL, token);
}

t_command	*parser(t_token *token)
{
	int			num_cmds;
	t_command	*commands;
	int			i;

	i = 0;
	num_cmds = get_number_of_commands(token);
	commands = ft_malloc(num_cmds * sizeof(t_command));
	while (i < num_cmds)
	{
		commands[i].tokens = ft_malloc((get_number_of_tokens(token) + 1)
				* sizeof(t_token *));
		commands[i].in_files = ft_malloc((get_number_of_infiles(token) + 1)
				* sizeof(t_redirect *));
		commands[i].out_files = ft_malloc((get_number_of_outfiles(token) + 1)
				* sizeof(t_redirect *));
		if (!commands[i].tokens || !commands[i].in_files
			|| !commands[i].out_files)
			return (NULL);
		token = parse_token(&commands[i], token);
		if (token)
			token = token->next;
		i++;
	}
	return (commands);
}
