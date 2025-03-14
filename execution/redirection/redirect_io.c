/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:24:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 02:20:16 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	fd = ft_open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	redirect_io(t_command cmd, char **heredoc, int heredoc_pos)
{
	open_in_files(cmd.in_files, heredoc, heredoc_pos);
	open_out_files(cmd.out_files);
}
