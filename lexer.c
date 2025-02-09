/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/09 16:58:13 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char *line)
{
	if (!is_valid_syntax(line))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n",
			STDERR_FILENO); // TODO show `'` token on error | check leaks
		exit(EXIT_SYNTAX_ERROR);
	}
	else
		printf("%s\n", line);
}
