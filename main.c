/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/01 14:45:32 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_token		*tokens;
	t_command	*commands;

	(void)env;
	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	init_env(env);
	while (1)
	{
		tokens = lexer();
		print_tokens(tokens);
		commands = parser(tokens);
		exec(commands);
		// print_commands(commands, get_number_of_commands(tokens));
		ft_free();
	}
	return (EXIT_SUCCESS);
}
