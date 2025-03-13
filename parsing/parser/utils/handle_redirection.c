/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:22:35 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:51 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(t_command *cmd, t_token *token, int *in_index,
		int *out_index)
{
	t_token		*next;
	t_redirect	*redir;

	next = token->next;
	redir = ft_malloc(sizeof(t_redirect));
	redir->file.value = next->value;
	redir->file.type = next->type;
	redir->type = token->type;
	if (token->type == t_greater || token->type == t_double_greater)
		cmd->out_files[(*out_index)++] = redir;
	else
		cmd->in_files[(*in_index)++] = redir;
}
