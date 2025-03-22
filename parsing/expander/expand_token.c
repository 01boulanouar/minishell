/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:04:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 16:26:10 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expand_token(t_token **token, char *line, char *value)
// {
// 	char	*name;
// 	t_token	*new_token;
// 	int		after_space;

// 	value++;
// 	name = ft_getenv(value);
// 	if (name)
// 	{
// 		after_space = ft_isin(*line, BLANKS);
// 		new_token = ft_lstnew_token(ft_strdup(name), t_expanded, after_space);
// 		ft_lstadd_back_token(token, new_token);
// 	}
// }

void	expand_token(t_token **token, char *name, int after_space)
{
	char			*expanded;
	char			*start;
	char			*value;

	if (!strncmp(name, EXIT_STATUS, 2))
		expanded = ft_itoa(*ft_get_exit_status());
	else
	{
		name++;
		expanded = ft_getenv(name);
	}
	if (!expanded)
	{
		value = ft_strdup("");
		ft_lstadd_back_token(token, ft_lstnew_token(value, t_expanded, after_space));
	}
	while (expanded && *expanded)
	{
		start = expanded;
		expanded += get_next_token_len(start);
		value = ft_copy(start, expanded);
		ft_lstadd_back_token(token, ft_lstnew_token(value, t_expanded, after_space));
		after_space = ft_isin(*expanded, BLANKS);
		expanded += ft_strspn(expanded, BLANKS);
	}
	return ;
}
