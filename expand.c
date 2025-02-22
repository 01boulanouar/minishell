/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/22 16:25:17 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_expand(t_token **token, char *name)
{
	char			*expanded;
	char			*start;
	char			*value;
	int				after_space;
	t_token_type	type;

	if (name[0] != DOLLAR)
		return (0);
	name++;
	after_space = 0;
	expanded = getenv(name);
	if (!expanded)
		return (0);
	while (*expanded)
	{
		start = expanded;
		expanded += lex_get_next_token(start);
		value = ft_copy(start, expanded);
		type = lex_token_type(value);
		ft_lstadd_back(token, ft_lstnew(value, type, after_space, 1));
		after_space = ft_isin(*expanded, BLANKS);
		expanded += ft_strspn(expanded, BLANKS);
	}
	return (1);
}
