/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 18:18:32 by moboulan         ###   ########.fr       */
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
			2))
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
	int				after_space;

	token = NULL;
	after_space = 0;
	while (*line)
	{
		start = line;
		line += get_next_token_len(line);
		value = ft_copy(start, line);
		type = get_token_type(value);
		if (type == t_double_quote)
			value = expand_double_quotes(value);
		if (type == t_dollar_expand || type == t_dollar_num)
			expand_token(&token, value, after_space);
		if (type != t_dollar_expand && type != t_dollar_num)
			ft_lstadd_back_token(&token, ft_lstnew_token(value, type,
					after_space, 0));
		after_space = ft_isin(*line, BLANKS);
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	char	*trim_line;
	char 	*tmp ; 
	token = NULL;
	if (!is_valid_quotes(line))
	{
		ft_putendl_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	trim_line = ft_trim(line);
	while (trim_line[ft_strlen(trim_line)-1]=='|')
	{
		tmp = readline("pipe> ");
		trim_line = ft_trim((ft_strjoin(trim_line,tmp)));
	}
	
	token = tokenize(trim_line);
	if (operator_error(token))
	{
		ft_putendl_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	// print_tokens(token);
	return (token);
}
