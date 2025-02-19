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
