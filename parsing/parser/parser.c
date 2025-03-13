/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:33:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/13 20:24:01 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		commands[i].in_files = ft_malloc((get_number_of_infiles(token) + 1)
				* sizeof(t_redirect *));
		commands[i].out_files = ft_malloc((get_number_of_outfiles(token) + 1)
				* sizeof(t_redirect *));
		if (!commands[i].tokens || !commands[i].in_files
			|| !commands[i].out_files)
			return (NULL);
		token = parse_token(&commands[i], token, &count);
		if (token)
			token = token->next;
		i++;
	}
	return (commands);
}
