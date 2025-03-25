/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 02:46:49 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_random_name(void)
{
	char	*name;

	name = ft_strjoin(HEREDOC_NAME, ft_itoa((int)ft_malloc(1)));
	return (name);
}

char	**init_herdoc(t_token *token)
{
	char	**heredoc;
	int		n_herdocs;

	n_herdocs = get_number_of_herdocs(token);
	heredoc = ft_malloc(n_herdocs * sizeof(char *));
	return (heredoc);
}

void	cleanup_heredocs(char **heredoc, int num_herdocs)
{
	int	i;

	i = 0;
	while (i < num_herdocs)
	{
		if (heredoc[i])
		{
			unlink(heredoc[i]);
			heredoc[i] = NULL;
		}
		i++;
	}
}

char	*read_from_heredoc(t_redirect *redirect, char **heredoc,
		int heredoc_index)
{
	char	*line;
	int		fd;
	char	*name;

	name = get_random_name();
	fd = ft_open_create(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = ft_readline("> ");
		if (!is_quotes(&redirect->file))
			line = expand_str(line);
		if (!line || ft_strcmp(line, redirect->file.value) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	heredoc[heredoc_index++] = ft_strdup(name);
	return (name);
}
