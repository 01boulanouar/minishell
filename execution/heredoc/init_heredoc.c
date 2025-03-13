/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 20:07:39 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_herdoc(t_token *token)
{
	char	**heredoc;
	int		n_herdocs;

	n_herdocs = get_number_of_herdocs(token);
	heredoc = ft_malloc(n_herdocs * sizeof(char *));
	return (heredoc);
}
