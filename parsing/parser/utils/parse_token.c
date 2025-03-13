/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:24:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 20:28:07 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parse_token(t_command *command, t_token *token,int *count)
{
	int	j;
	int	in_index;
	int	out_index;
	
	j = 0;
	in_index = 0;
	out_index = 0;
	command->heredoc_pos= *count ; 
	while (token)
	{
		if (token->type == t_pipe)
			break ;
		if (is_redirection(token))
		{
			if (token->next && token->next->next)
				command->not_to_be_executed = 1;
			if (token->type == t_double_less)
				(*count)++; 
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
