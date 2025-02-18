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

int	files_number(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != t_pipe)
	{
		if (is_redirection(token))
			count++;
		;
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

// void	handle_redirection(t_comand *cmd, t_token *token, char **tmp_out,
// 		char **tmp_in)
// {
// 	t_token	*next;

// 	next = token->next;
// 	if (token->type == t_greater || token->type == t_dgreater)
// 	{
// 		cmd->out.file = next->value;
// 		if (token->type == t_greater)
// 			*tmp_out = next->value;
// 		if (token->type == t_dgreater && ft_strcmp(*tmp_out, next->value) == 0)
// 			cmd->out.type = t_greater;
// 		else
// 			cmd->out.type = token->type;
// 	}
// 	else
// 	{
// 		cmd->in.file = next->value;
// 		if (token->type == t_less)
// 			*tmp_in = next->value;
// 		if (token->type == t_dless && ft_strcmp(*tmp_in, next->value) == 0)
// 			cmd->in.type = t_less;
// 		else
// 			cmd->in.type = token->type;
// 	}
// }

// t_token	*ft_parse(t_comand *comand, t_token *token)
// {
// 	int		j;
// 	char	*tmp_out;
// 	char	*tmp_in;

// 	tmp_out = NULL;
// 	tmp_in = NULL;
// 	j = 0;
// 	while (token && token->type != t_pipe)
// 	{
// 		if (is_redirection(token))
// 		{
// 			handle_redirection(comand, token, &tmp_out, &tmp_in);
// 			token = token->next;
// 		}
// 		else
// 		{
// 			comand->tokens[j++] = token;
// 		}
// 		token = token->next;
// 	}
// 	comand->tokens[j] = NULL;
// 	return (token);
// }

void	handle_redirection(t_comand *cmd, t_token *token, char **tmp_out,
		char **tmp_in, int *file_index)
{
	t_token	*next;

	next = token->next;
	cmd->files[*file_index] = next->value;
	(*file_index)++;
	if (token->type == t_greater || token->type == t_dgreater)
	{
		cmd->out.file = next->value;
		if (token->type == t_greater)
			*tmp_out = next->value;
		if (token->type == t_dgreater && *tmp_out && ft_strcmp(*tmp_out,
				next->value) == 0)
			cmd->out.type = t_greater;
		else
			cmd->out.type = token->type;
	}
	else
	{
		cmd->in.file = next->value;
		if (token->type == t_less)
			*tmp_in = next->value;
		if (token->type == t_dless && *tmp_in && ft_strcmp(*tmp_in,
				next->value) == 0)
			cmd->in.type = t_less;
		else
			cmd->in.type = token->type;
	}
}

t_token	*ft_parse(t_comand *comand, t_token *token)
{
	int		j;
	int		file_index;
	char	*tmp_out;
	char	*tmp_in;

	tmp_out = NULL;
	tmp_in = NULL;
	j = 0;
	file_index = 0;
	while (token && token->type != t_pipe)
	{
		if (is_redirection(token))
		{
			handle_redirection(comand, token, &tmp_out, &tmp_in, &file_index);
			token = token->next;
		}
		else
		{
			comand->tokens[j++] = token;
		}
		token = token->next;
	}
	comand->tokens[j] = NULL;
	comand->files[file_index] = NULL;
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
		comands[i].files = malloc((files_number(token) + 1) * sizeof(char *));
		if (!comands[i].tokens)
			return (NULL);
		comands[i].in.file = NULL;
		comands[i].out.file = NULL;
		token = ft_parse(&comands[i], token);
		if (token)
			token = token->next;
		i++;
	}
	return (comands);
}

//
