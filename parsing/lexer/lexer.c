/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/24 22:34:09 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

t_token	*lexer(void)
{
	t_token	*token;
	char	*line;

	token = NULL;
	line = ft_readline("minishell> ");
	if (!is_valid_quotes(line))
	{
		print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
		ft_set_exit_status(EXIT_SYNTAX_ERROR);
		return (NULL);
	}
	if (line && ft_strcmp(line, ""))
		add_history(line);
	token = tokenize(line);
	join_token(&token);
	if (is_valid_operator(token))
	{
		print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
		ft_set_exit_status(EXIT_SYNTAX_ERROR);
		return (NULL);
	}
	return (token);
}
