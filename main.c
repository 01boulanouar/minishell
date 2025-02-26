/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/26 13:08:01 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	init_env(env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (EXIT_SUCCESS);
		add_history(line);
		tokens = lexer(line);
		free(line);
		commands = parser(tokens);
		exec(commands);
		// print_commands(commands, num);
		ft_free();
	}
	ft_lstfree_env();
	return (EXIT_SUCCESS);
}
