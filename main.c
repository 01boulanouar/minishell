/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/27 01:23:40 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_token		*tokens;
	t_command	*commands;
	char		**heredoc;
	char		**line;
	int			i;
	int			last_exit_status;

	(void)env;
	(void)argv;
	g_in_shell = 1;
	// if (argc != 1 || !isatty(STDIN_FILENO))
	// 	ft_exit(EXIT_FAILURE);
	init_env(env);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
	{
		line = ft_split(argv[2], ';');
		if (!line)
			ft_exit(EXIT_FAILURE);
		i = 0;
		last_exit_status = 0;
		while (line[i])
		{
			tokens = tokenize(ft_trim(line[i]));
			if (!tokens)
			{
				i++;
				continue ;
			}
			if (is_valid_operator(tokens))
			{
				print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
				ft_set_exit_status(EXIT_SYNTAX_ERROR);
				return (2);
			}
			join_token(&tokens);
			commands = parser(tokens);
			heredoc = init_heredoc(tokens);
			exec(commands, get_number_of_commands(tokens), heredoc,
				get_number_of_heredocs(tokens));
			last_exit_status = *ft_get_exit_status();
			i++;
		}
		return (last_exit_status);
	}
	else
	{
		while (1)
		{
			tokens = lexer();
			if (!tokens)
				continue ;
			commands = parser(tokens);
			heredoc = init_heredoc(tokens);
			exec(commands, get_number_of_commands(tokens), heredoc,
				get_number_of_heredocs(tokens));
			ft_free();
		}
	}
	ft_free_env();
	return (EXIT_SUCCESS);
}
