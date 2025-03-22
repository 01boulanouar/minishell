/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 17:40:41 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(void)
{
	t_token	*token;
	char	*trim_line;
	char	*line;
	int		inside_pipe;
	char	*tmp;

	token = NULL;
	trim_line = NULL;
	inside_pipe = 0;
	while (1)
	{
		if (inside_pipe)
			line = ft_readline("> ");
		else
			line = ft_readline("minishell> ");
		trim_line = ft_strjoin_space(trim_line, line);
		if (!trim_line)
			return (token);
		if (!is_valid_quotes(line) || (line && ft_trim(line)[0] == '|'))
		{
			print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
			ft_exit(EXIT_SYNTAX_ERROR);
		}
		tmp = ft_trim(trim_line);
		if ((ft_strlen(tmp) && tmp[ft_strlen(tmp) - 1] != '|')
			|| !ft_strlen(line))
			break ;
		inside_pipe = 1;
	}
	if (trim_line && ft_strlen(trim_line))
		add_history(trim_line);
	token = tokenize(trim_line);
	join_token(&token);
	if (is_valid_operator(token))
	{
		print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
		ft_exit(EXIT_SYNTAX_ERROR);
	}
	return (token);
}
