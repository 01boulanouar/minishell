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

void	handle_redirection(t_comand *cmd, t_token *token, char **tmp_out,
		char **tmp_in)
{
	t_token	*next;

	next = token->next;
	if (token->type == t_greater || token->type == t_dgreater)
	{
		if (!cmd->out.file || (cmd->out.type == t_dgreater
				&& token->type == t_greater) || (cmd->out.file
				&& ft_strcmp(cmd->out.file, next->value) != 0))
		{
			cmd->out.file = next->value;
			cmd->out.type = token->type;
			// Only update tmp_out when encountering >
			if (token->type == t_greater)
			{
				*tmp_out = next->value;
			}
		}
		else if (token->type == t_dgreater && *tmp_out && ft_strcmp(*tmp_out,
				next->value) == 0)
		{
			cmd->out.type = t_greater;
		}
	}
	else if (token->type == t_less || token->type == t_dless)
	{
		if (!cmd->in.file || (cmd->in.type == t_dless && token->type == t_less)
			|| (cmd->in.file && ft_strcmp(cmd->in.file, next->value) != 0))
		{
			cmd->in.file = next->value;
			cmd->in.type = token->type;
			// Only update tmp_in when encountering <
			if (token->type == t_less)
				*tmp_in = next->value;
		}
		else if (token->type == t_dless && *tmp_in && ft_strcmp(*tmp_in,
				next->value) == 0)
		{
			// If << matches the last < file, downgrade type
			cmd->in.type = t_less;
		}
	}
}

// void	handle_redirection1(t_comand *cmd, t_token *token, char **tmp_out,
// 		char **tmp_in){
// 	t_token	*next;

// 	next = token->next;
// 	if (token->type == t_greater || token->type == t_dgreater){
// 		if (!cmd->out.file  || (cmd->out.file
// 				&& ft_strcmp(cmd->out.file, next->value) != 0)){

// 				}
// 	}
// }

t_token	*ft_redirect(t_comand *comand, t_token *token)
{
	int		j;
	char	*tmp_out;
	char	*tmp_in;

	tmp_out = NULL;
	tmp_in = NULL;
	j = 0;
	while (token && token->type != t_pipe)
	{
		if (is_redirection(token))
		{
			handle_redirection(comand, token, &tmp_out, &tmp_in);
			token = token->next;
		}
		else
		{
			comand->tokens[j++] = token;
		}
		token = token->next;
	}
	comand->tokens[j] = NULL;
	return (token);
}

t_comand	*parse(t_token *token)
{
	t_comand	*comands;
	int			i;
	int			num_cmds;

	num_cmds = number_of_commands(token);
	comands = malloc(num_cmds * sizeof(t_comand));
	if (!comands)
		return (NULL);
	i = 0;
	while (i < num_cmds)
	{
		comands[i].tokens = malloc((n_tokens(token) + 1) * sizeof(t_token *));
		if (!comands[i].tokens)
			return (NULL);
		comands[i].in.file = NULL;
		comands[i].out.file = NULL;
		token = ft_redirect(&comands[i], token);
		if (token)
			token = token->next;
		i++;
	}
	return (comands);
}
