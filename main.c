/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 01:09:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_token		*tokens;
	t_command	*commands;
	char		**heredoc;

	(void)env;
	(void)argv;
	if (argc != 1 || !isatty(STDIN_FILENO))
		ft_exit(EXIT_FAILURE);
	init_env(env);
	while (1)
	{
		tokens = lexer();
		// print_tokens(tokens);
		commands = parser(tokens);
		heredoc = init_herdoc(tokens);
		exec(commands, get_number_of_commands(tokens),
			heredoc, get_number_of_herdocs(tokens));
		ft_free();
	}
	ft_free_env();
	return (EXIT_SUCCESS);
}
