/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 08:59:11 by aelkadir         ###   ########.fr       */
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

	(void)env;
	(void)argv;
	// if (argc != 1 || !isatty(STDIN_FILENO))
	// 	ft_exit(EXIT_FAILURE);
	init_env(env);
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
	{
		line = ft_split(argv[2], ';');
		if (!line)
			ft_exit(EXIT_FAILURE);
		i = 0;
		int last_exit_status = 0; // Store the last exit status
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
			// print_tokens(tokens);
			commands = parser(tokens);
			heredoc = init_herdoc(tokens);
			exec(commands, get_number_of_commands(tokens), heredoc,
				get_number_of_herdocs(tokens));
			// Retrieve the exit status after executing the command
			last_exit_status = *ft_get_exit_status();
			i++;
		}
		return (last_exit_status);
			// Ensure the last command's exit status is returned
	}
	else
	{
		while (1)
		{
			tokens = lexer();
			if (!tokens)
				continue ;
			// print_tokens(tokens);
			commands = parser(tokens);
			// print_commands(commands, get_number_of_commands(tokens));
			heredoc = init_herdoc(tokens);
			exec(commands, get_number_of_commands(tokens), heredoc,
				get_number_of_herdocs(tokens));
			ft_free();
		}
	}
	ft_free_env();
	return (EXIT_SUCCESS);
}
