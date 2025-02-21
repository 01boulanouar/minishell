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

t_token	*ft_parse(t_comand *comand, t_token *token)
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
			handle_redirection(comand, token, &in_index, &out_index);
			token = token->next;
		}
		else
			comand->tokens[j++] = token;
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
	comands = ft_malloc(num_cmds * sizeof(t_comand));
	while (i < num_cmds)
	{
		comands[i].tokens = ft_malloc((n_tokens(token) + 1)
				* sizeof(t_token *));
		comands[i].in_files = ft_malloc((in_files_number(token) + 1)
				* sizeof(t_redirect *));
		comands[i].out_files = ft_malloc((out_files_number(token) + 1)
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
