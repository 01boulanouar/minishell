/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/11 20:31:19 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	join_token(t_token **token)
// {
// 	t_token	*current;
// 	t_token	*next_token;

// 	current = *token;
// 	while (current && current->next)
// 	{
// 		next_token = current->next;
// 		if (next_token && !next_token->after_space && !is_operator(current)
// 			&& !is_operator(next_token))
// 			{
// 			if(next_token->type==t_expanded && next_token->value
// 					&& !ft_strcmp(next_token->value, "")){
// 					printf("1");
// 					next_token->after_space = 1;
// 				}
// 			if (current->next->type == t_double_quote
// 				|| current->next->type == t_single_quote)
// 				current->type = current->next->type;

// 			else
// 				{current->value = ft_strjoin(current->value, next_token->value);
// 				}
// 				current->next = next_token->next;
// 				next_token->after_space = current->after_space;
// 		}
// 		else
// 			current = current->next;
// 	}
// }

void	join_token(t_token **token)
{
	t_token	*current;
	t_token	*next_token;

	current = *token;
	while (current && current->next)
	{
		next_token = current->next;
		if (next_token->type == t_expanded && next_token->value
			&& !ft_strcmp(next_token->value, ""))
		{
			// If no after_space, treat it as a splitter:
			// mark the token after it with after_space = 1
			if (!next_token->after_space && next_token->next)
				next_token->next->after_space = 1;
			current = current->next;
			continue ;
		}
		if (current->type == t_expanded && current->value
			&& !ft_strcmp(current->value, ""))
		{
			current = current->next;
			continue ;
		}
		if (!next_token->after_space && !is_operator(current)
			&& !is_operator(next_token))
		{
			// Inherit quote type if applicable
			if (next_token->type == t_double_quote
				|| next_token->type == t_single_quote)
				current->type = next_token->type;
			current->value = ft_strjoin(current->value, next_token->value);
			current->next = next_token->next;
		}
		else
		{
			current = current->next;
		}
	}
}

static int	handle_special_cases(const char *start, char *value)
{
	if ((!ft_strncmp(start, "$\"", 2) || !ft_strncmp(start, "$\'", 2))
				&& ft_strlen(value) == 1)
		return (1);
	return (0);
}

static void	add_token_to_list(t_token **token, char *value, t_token_type type,
		int after_space)
{
	static int	a_s;

	if (a_s == 1)
	{
		after_space = a_s;
		a_s = 0;
	}
	if (type == t_double_quote && !is_dollar_str(value))
		value = expand_str(value);
	if ((type == t_dollar_expand || type == t_dollar_num
		|| type == t_exit_status) && ft_last_token(token)->type!=t_double_less)
	{
		a_s = expand_token(token, value, after_space);
	}
	else
		ft_lstadd_back_token(token, ft_lstnew_token(value, type, after_space));
}

t_token	*tokenize(char *line)
{
	const char		*start;
	t_token			*token;
	t_token_type	type;
	int				after_space;
	char			*value;

	after_space = 0;
	token = NULL;
	if (!line)
		return (NULL);
	line += ft_strspn(line, BLANKS);
	while (*line)
	{
		start = line;
		line += get_next_token_len(line);
		value = ft_copy(start, line);
		if (handle_special_cases(start, value))
			continue ;
		type = get_token_type(value);
		add_token_to_list(&token, value, type, after_space);
		after_space = ft_isin(*line, BLANKS);
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}

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
