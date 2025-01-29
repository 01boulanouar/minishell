/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:13:16 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/29 19:52:27 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(const char *line)
{
	char	**split;
	int		i;

	split = ft_split(line, BLANKS);
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free(split, i);
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
