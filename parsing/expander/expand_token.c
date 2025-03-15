/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:04:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/15 23:23:11 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expand_token(t_token **token, char *line, char *value)
// {
// 	char	*name;
// 	t_token	*new_token;
// 	int		before_space;

// 	value++;
// 	name = ft_getenv(value);
// 	if (name)
// 	{
// 		before_space = ft_isin(*line, BLANKS);
// 		new_token = ft_lstnew_token(ft_strdup(name), t_expanded, before_space);
// 		ft_lstadd_back_token(token, new_token);
// 	}
// }

void	expand_token(t_token **token, char *name)
{
	char			*expanded;
	char			*start;
	char			*value;

	name++;
	expanded = ft_getenv(name);
	while (expanded && *expanded)
	{
		start = expanded;
		expanded += get_next_token_len(start);
		value = ft_copy(start, expanded);
		ft_lstadd_back_token(token, ft_lstnew_token(value, t_expanded, ft_isin(*expanded, BLANKS)));
		expanded += ft_strspn(expanded, BLANKS);
	}
	return ;
}