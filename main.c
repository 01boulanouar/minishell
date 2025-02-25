/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 17:11:33 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;
	int			num;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		tokens = lexer(line);
		free(line);
		num = get_number_of_commands(tokens);
		commands = parser(tokens);
		exec(commands, tokens);
		// print_commands(commands, num);
		ft_free();
	}
	return (0);
}
