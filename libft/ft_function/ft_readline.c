/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:22:57 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/27 00:04:19 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *prompt)
{
	char	*line;
	char	*tmp;

	tmp = readline(prompt);
	if (!tmp && g_in_shell == 1)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_exit(EXIT_SUCCESS);
	}
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}
