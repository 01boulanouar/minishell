/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:22:57 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:12:22 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *prompt)
{
	char	*line;
	char	*tmp;

	tmp = readline(prompt);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}
