/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/08 03:53:40 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*tokenize(char *line)
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
			expand(&token, line, value);
		if (type != t_dollar_expand && type != t_dollar_num && type != t_single_dollar)
			ft_lstadd_back_token(&token, ft_lstnew_token(value, type,
					ft_isin(*line, BLANKS)));
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

static void	join_token(t_token **token)
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
			current->value = ft_strjoin(current->value, next_token->value);
			current->next = next_token->next;
			current->before_space = next_token->before_space;
		}
		else
			current = current->next;
	}
}

static char *ft_readline(const char *prompt)
{
	char 	*line;
	char	*tmp;
	
	tmp = readline(prompt);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
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
			line = ft_readline("> ");
		else
			line = ft_readline("minishell> ");
		trim_line = ft_strjoin_space(trim_line, line);
		if (!trim_line)
			return (token);
		if (!is_valid_quotes(line) || (line && ft_trim(line)[0] == '|'))
		{
			print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
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
		print_error(1, NULL, NULL, SYNTAX_ERROR_STR);
		exit(EXIT_SYNTAX_ERROR);
	}
	return (token);
}
