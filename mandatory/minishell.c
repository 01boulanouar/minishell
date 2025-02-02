/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:13:16 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/02 17:45:43 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(const char *line)
{
	const char	*start;
	char		*token;

	line += ft_strspn(line, DELIM);
	while (line < line + ft_strlen(line))
	{
		start = line;
		line += ft_strcspn(line, DELIM);
		token = ft_copy(start, line);
		printf("%s\n", token);
		free(token);
		line += ft_strspn(line, DELIM);
	}
	return ;
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		parse_line(line);
		free(line);
	}
	return (0);
}
