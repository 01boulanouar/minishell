/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/14 13:06:00 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_random_name(void)
{
	char	*name;
	int		num;

	num = (int)ft_malloc(1);
	name = ft_strjoin(HEREDOC_NAME, ft_itoa(num));
	return (name);
}

char	**init_heredoc(t_token *token)
{
	char	**heredoc;
	int		n_heredocs;

	n_heredocs = get_number_of_heredocs(token);
	if (n_heredocs > 16)
	{
		print_error(1, NULL, NULL, "maximum here-document count exceeded");
		ft_exit(2);
	}
	heredoc = ft_malloc(n_heredocs * sizeof(char *));
	return (heredoc);
}

void	cleanup_heredocs(char **heredoc, int num_heredocs)
{
	int	i;

	i = 0;
	while (i < num_heredocs)
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
	heredoc[heredoc_index++] = ft_strdup(name);
	fd = ft_open_create(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	g_in_shell = 2;
	while (1)
	{
		line = ft_readline("> ");
		if (!is_quotes(&redirect->file) && (line && ft_strcmp(line,
					redirect->file.value)))
			line = expand_str(line);
		if (!line || !ft_strcmp(line, redirect->file.value))
			break ;
		if (g_in_shell == 3)
			return (NULL);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (name);
}
