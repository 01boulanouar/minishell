/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/28 17:11:26 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_next_quote_token(const char *line)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (line[0] == SINGLE_QUOTE)
		quote = SINGLE_QUOTE;
	else if (line[0] == DOUBLE_QUOTE)
		quote = DOUBLE_QUOTE;
	if (quote)
	{
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] == quote)
			i++;
	}
	return (i);
}

size_t	get_next_token_len(const char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strncmp(line, DOUBLE_LESS, 2) || !ft_strncmp(line, DOUBLE_GREATER,
			2) || !ft_strncmp(line, EXIT_STATUS, 2))
		return (2);
	else if (line[0] == LESS || line[0] == GREATER || line[0] == PIPE
		|| (line[0] == DOLLAR && !line[1]))
		return (1);
	else if (line[0] == SINGLE_QUOTE || line[0] == DOUBLE_QUOTE)
		return (get_next_quote_token(line));
	else
	{
		if (line[0] == DOLLAR)
		{
			if (ft_isdigit(line[1]))
				return (2);
			i++;
		}
		while (line[i] && !ft_isin(line[i], SEPARATORS))
			i++;
	}
	return (i);
}

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
			line = readline("> ");
		else
			line = readline("minishell> ");
		trim_line = ft_strjoin_space(trim_line, line);
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
	add_history(trim_line);
	token = tokenize(trim_line);
	// print_tokens(token);
	return (token);
}
