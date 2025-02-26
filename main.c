/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 18:43:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*tokens;
	t_env		*envs;
	t_command	*commands;
	int			num;

	(void) argv;

	if (argc != 1)
		exit(EXIT_FAILURE);
	envs = handle_env(env);
	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		tokens = lexer(line);
		free(line);
		num = get_number_of_commands(tokens);
		commands = parser(tokens);
		exec(commands, tokens, envs);
		print_commands(commands, num);
		// ft_free();
	}
	return (0);
}
