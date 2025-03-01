/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/01 14:25:15 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	const char		*start;
	t_token			*token;
	t_token_type	type;
	char			*value;

	token = NULL;
	line += ft_strspn(line, BLANKS);
	while (*line)
	{
		start = line;
		line += get_next_token_len(line);
		value = ft_copy(start, line);
		type = get_token_type(value);
		if (type == t_double_quote)
			value = expand_double_quotes(value);
		if (type == t_dollar_expand || type == t_dollar_num)
			expand_token(&token, value, ft_isin(*line, BLANKS));
		if (type != t_dollar_expand && type != t_dollar_num)
			ft_lstadd_back_token(&token, ft_lstnew_token(value, type,
					ft_isin(*line, BLANKS), 0));
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

void	join_token(t_token **token)
{
	t_token	*current;
	t_token	*next_token;

	current = *token;
	while (current && current->next)
	{
		next_token = current->next;
		if (next_token && !current->before_space && !is_operator(current)
			&& !is_operator(next_token))
		{
			current->value = ft_strjoin(current->value, next_token->value, 0);
			current->next = next_token->next;
			current->before_space = next_token->before_space;
		}
		else
			current = current->next;
	}
}

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
		{
			tmp = readline("> ");
			line = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			tmp = readline("minishell> ");
			line = ft_strdup(tmp);
			free(tmp);
		}
		trim_line = ft_strjoin(trim_line, line, 1);
		if (!trim_line)
			return (token);
		if (!is_valid_quotes(line) || (line && ft_trim(line)[0] == '|'))
		{
			ft_putendl_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
			exit(EXIT_SYNTAX_ERROR);
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
	if (operator_error(token))
	{
		ft_putendl_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	// print_tokens(token);
	return (token);
}
