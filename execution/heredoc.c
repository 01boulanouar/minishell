/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/09 04:28:10 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_random_name(void)
{

	char	*name;

	name = ft_malloc(0);
	return (ft_strjoin(HEREDOC_NAME, ft_itoa((long)&name)));
}


void heredoc(t_redirect *redirection)
{
	int expand;

	expand = 0;
	if (redirection->file.type == t_double_quote || redirection->file.type == t_single_quote)
		expand = 1;
	
	printf("name = %s\n, expand = %d , delim = %s\n", get_random_name(), expand, redirection->file.value);
}
