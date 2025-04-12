/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/12 16:01:49 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_token		*tokens;
	t_command	*commands;
	char		**heredoc;

	(void)argv;
	if (argc != 1 || !isatty(STDIN_FILENO))
		ft_exit(EXIT_FAILURE);
	g_in_shell = 1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_env(env);
	while (1)
	{
		save_terminal_settings();
		tokens = lexer();
		// print_tokens(tokens);
		if (!tokens)
			continue ;
		commands = parser(tokens);
		heredoc = init_heredoc(tokens);
		exec(commands, get_number_of_commands(tokens), heredoc,
			get_number_of_heredocs(tokens));
		ft_free();
	}
	ft_free_env();
	return (EXIT_SUCCESS);
}
