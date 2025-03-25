/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:33 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 04:56:39 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_token_type(t_token_type type)
{
	if (type == t_pipe)
		return ("|");
	else if (type == t_single_dollar)
		return ("$");
	else if (type == t_dollar_num)
		return ("DOLLAR NUM");
	else if (type == t_dollar_expand)
		return ("DOLLAR EXPAND");
	else if (type == t_exit_status)
		return ("$?");
	else if (type == t_less)
		return ("<");
	else if (type == t_greater)
		return (">");
	else if (type == t_double_less)
		return ("<<");
	else if (type == t_double_greater)
		return (">>");
	else if (type == t_single_quote)
		return ("\'");
	else if (type == t_double_quote)
		return ("\"");
	else if (type == t_word)
		return ("WORD");
	else if (type == t_expanded)
		return ("Expanded");
	else
		return ("UNKOWN");
}

void	print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("[%s] %s after_space %d\n", token->value,
			print_token_type(token->type), token->after_space);
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
		printf("[  --");
		while (commands[i].tokens[j])
		{
			printf("%s ", commands[i].tokens[j]->value);
			j++;
		}
		printf("--   ]");
		printf("\n");
		k = 0;
		if (commands[i].files[0])
			printf("          --files--\n");
		while (commands[i].files[k])
		{
			printf("          file [%d] : %s \t %s\n", k,
				commands[i].files[k]->file.value,
				print_token_type(commands[i].files[k]->type));
			k++;
		}
		i++;
	}
}
