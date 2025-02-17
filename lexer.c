/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/17 17:44:17 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lex_skip_quotes(const char *line)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (line[i] == SQUOTE)
		quote = SQUOTE;
	else if (line[i] == DQUOTE)
		quote = DQUOTE;
	if (quote)
	{
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] == quote)
			i++;
	}
	else
	{
		while (line[i] && !ft_isin(line[i], SEPARATORS))
			i++;
	}
	return (i);
}

t_token	*lex_tokenize(char *line)
{
	const char		*start;
	t_token			*token;
	char			*value;
	int				a_space;

	token = NULL;
	a_space = 0;
	while (*line)
	{
		start = line;
		if (*line == LESS || *line == GREATER || *line == PIPE)
			line++;
		else
			line += lex_skip_quotes(line);
		if (((*line == LESS || *line == GREATER) && *line == *start))
			line++;
		value = ft_copy(start, line);
		if (!value)
			return (token);
		ft_lstadd_back(&token, ft_lstnew(value, lex_t_type(value), a_space));
		a_space = ft_isin(*line, BLANKS);
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

char	*lex_trim(char *line)
{
	const char	*start;
	const char	*end;

	start = line;
	end = line + ft_strlen(line);
	while (*start && ft_isin(*start, BLANKS))
		start++;
	while (end >= start && ft_isin(*end, BLANKS))
		end--;
	return (ft_copy(start, end));
}

void	lex_print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("[%s] %s %d\n", token->value, lex_print_token_type(token->type),
			token->token_after_space);
		token = token->next;
	}
}

static void	print_commands(t_comand *commands, int num_commands)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_commands)
	{
		printf("Command %d: ", i + 1);
		j = 0;
		while (commands[i].tokens[j])
		{
			printf("%s ", commands[i].tokens[j]->value);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	lexer(char *line)
{
	t_token		*token;
	char		*trim_line;
	int			num;
	t_comand	*comands;

	token = NULL;
	if (!lex_is_valid_syntax(line))
	{
		ft_putstr_fd(SYNTAX_ERROR_STR, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	trim_line = lex_trim(line);
	free(line);
	line = NULL;
	token = lex_tokenize(trim_line);
	num = number_of_commands(token);
	comands = parse(token);
	print_commands(comands, num);
	free(trim_line);
	trim_line = NULL;
	// lex_print_tokens(token);
	// ft_lstfree(&token);
}
