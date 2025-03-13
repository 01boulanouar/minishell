/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 14:35:35 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_expand(t_redirect *redirection)
{
	int	expand;

	expand = 0;
	if (redirection->file.type == t_double_quote
		|| redirection->file.type == t_single_quote)
		expand = 1;
	printf("name = %s\n, expand = %d , delim = %s\n", get_random_name(), expand,
		redirection->file.value);
}

char	**init_herdoc(t_token *token)
{
	char	**heredoc;
	int		n_herdocs;

	n_herdocs = get_number_of_herdocs(token);
	heredoc = ft_malloc(n_herdocs * sizeof(char *));
	return (heredoc);
}
