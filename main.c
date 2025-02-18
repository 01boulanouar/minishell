/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 16:10:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_commands(t_comand *commands, int num_commands)
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
		if (commands[i].out.file)
			printf("          out_file : [%s :] [ %s] \n", commands[i].out.file,
				lex_print_token_type(commands[i].out.type));
		if (commands[i].in.file)
			printf("          in__file : [%s :] [ %s] \n", commands[i].in.file,
				lex_print_token_type(commands[i].in.type));
		k = 0;
		if (commands[i].files[0])
			printf("          --files--\n");
		while (commands[i].files[k])
		{
			printf("          file [%d] : %s \n", k, commands[i].files[k]);
			k++;
		}
		i++;
	}
}

void	f(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char		*line;
	t_token		*token;
	t_comand	*comands;
	int			num;

	atexit(f);
	while (1)
	{
		line = readline("minishell>");
		add_history(line);
		token = lexer(line);
		num = number_of_commands(token);
		comands = parse(token);
		print_commands(comands, num);
		ft_lstfree(&token);
	}
	return (0);
}
