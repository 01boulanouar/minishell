/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:33 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 16:34:38 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_token_type(t_token_type type)
{
	if (type == t_pipe)
		return ("PIPE");
	else if (type == t_single_dollar)
		return ("DOLLAR");
	else if (type == t_dollar_num)
		return ("DOLLAR NUM");
	else if (type == t_dollar_expand)
		return ("DOLLAR EXPAND");
	else if (type == t_less)
		return ("LESS");
	else if (type == t_greater)
		return ("GREATER");
	else if (type == t_double_less)
		return ("DOUBLE LESS");
	else if (type == t_double_greater)
		return ("DOUBLE GREATER");
	else if (type == t_single_quote)
		return ("SINGLE_QUOTES");
	else if (type == t_double_quote)
		return ("DOUBLE_QUOTES");
	else if (type == t_word)
		return ("WORD");
	else
		return ("UNKOWN");
}

void	print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("[%s] %s space %d expanded %d\n", token->value,
			print_token_type(token->type), token->after_space, token->expanded);
		token = token->next;
	}
}

void	print_commands(t_command *commands, int num_commands)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < num_commands)
	{
		printf("Command %d: ", i + 1);
		j = 0;
		printf("[  ");
		while (commands[i].tokens[j])
		{
			printf(" %s", commands[i].tokens[j]->value);
			j++;
		}
		printf("   ]");
		printf("\n");
		k = 0;
		if (commands[i].in_files[0])
			printf("          --in_files--\n");
		while (commands[i].in_files[k])
		{
			printf("          file [%d] : %s \t %s\n", k,
				commands[i].in_files[k]->file, commands[i].in_files[k]->type);
			k++;
		}
		if (commands[i].out_files[0])
			printf("          --out_files--\n");
		k = 0;
		while (commands[i].out_files[k])
		{
			printf("          file [%d] : %s \t %s\n", k,
				commands[i].out_files[k]->file, commands[i].out_files[k]->type);
			k++;
		}
		i++;
	}
}
