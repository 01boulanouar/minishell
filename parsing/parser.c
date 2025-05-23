/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:33:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/27 04:46:42 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar_str(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == DOLLAR || str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		i++;
	return (ft_strlen(str) == i);
}

void	handle_redirection(t_command *cmd, t_token *token, int *index)
{
	t_token		*next;
	t_redirect	*redir;

	next = token->next;
	redir = ft_malloc(sizeof(t_redirect));
	redir->file.value = next->value;
	redir->file.type = next->type;
	redir->type = token->type;
	cmd->files[(*index)++] = redir;
}

t_token	*parse_token(t_command *command, t_token *token, int *count)
{
	int	j;
	int	index;

	j = 0;
	index = 0;
	command->heredoc_pos = *count;
	command->not_to_be_executed = 0;
	command->is_last = 0;
	while (token)
	{
		if (token->type == t_pipe)
			break ;
		if (is_redirection(token))
		{
			if (token->type == t_double_less)
				(*count)++;
			handle_redirection(command, token, &index);
			token = token->next;
		}
		else
			command->tokens[j++] = token;
		token = token->next;
	}
	return (command->tokens[j] = NULL, command->files[index] = NULL, token);
}

t_command	*parser(t_token *token)
{
	int			num_cmds;
	t_command	*commands;
	int			i;
	int			count;

	count = 0;
	i = 0;
	num_cmds = get_number_of_commands(token);
	commands = ft_malloc(num_cmds * sizeof(t_command));
	while (i < num_cmds)
	{
		commands[i].tokens = ft_malloc((get_number_of_tokens(token) + 1)
				* sizeof(t_token *));
		commands[i].files = ft_malloc((get_number_of_files(token) + 1)
				* sizeof(t_redirect *));
		if (!commands[i].tokens || !commands[i].files)
			return (NULL);
		token = parse_token(&commands[i], token, &count);
		if (token)
			token = token->next;
		i++;
	}
	commands[i - 1].is_last = 1;
	return (commands);
}
