/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:08 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:54 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_token		*token;
	t_comand	*comands;
	int			num;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		token = lexer(line);
		free(line);
		num = get_number_of_commands(token);
		comands = parser(token);
		print_commands(comands, num);
		ft_free();
	}
	return (0);
}
