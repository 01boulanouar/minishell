/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:23:23 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/24 22:34:04 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	const char		*start;
	t_token			*token;
	t_token_type	type;
	int				after_space;
	char			*value;

	after_space = 0;
	token = NULL;
	line += ft_strspn(line, BLANKS);
	while (*line)
	{
		start = line;
		line += get_next_token_len(line);
		value = ft_copy(start, line);
		if (!ft_strncmp(value, "$", 1) && ft_strlen(value) == 1)
			continue ;
		type = get_token_type(value);
		if (type == t_double_quote)
			value = expand_str(value);
		if (type == t_dollar_expand || type == t_dollar_num || type == t_exit_status)
			expand_token(&token, value, after_space);
		if (type != t_dollar_expand && type != t_dollar_num
			&& type != t_single_dollar && type != t_exit_status)
			ft_lstadd_back_token(&token, ft_lstnew_token(value, type, after_space));
		after_space = ft_isin(*line, BLANKS);
		line += ft_strspn(line, BLANKS);
	}
	return (token);
}
