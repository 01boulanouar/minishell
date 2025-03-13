/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:24:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 20:36:31 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredocs(char **heredoc, int num_herdocs)
{
	for (int i = 0; i < num_herdocs; i++)
	{
		if (heredoc[i])
		{
			unlink(heredoc[i]);
			heredoc[i] = NULL;
		}
	}
}

char	*read_from_heredoc(t_redirect *redirect, char **heredoc, int heredoc_index)
{
	char	*line;
	int		fd;
	char	*name;

	name = get_random_name();
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc temporary file creation error");
		exit(EXIT_FAILURE);
	}
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



static void	open_in_files(t_redirect **in_files, char **heredoc, int heredoc_pos)
{
	int	in_fd;

	in_fd = -1;
	if (in_files && *in_files)
	{
		for (int i = 0; in_files[i]; i++)
		{
			if (in_fd != -1)
				close(in_fd);
			if (in_files[i]->type == t_double_less)
			{
				in_fd = open(heredoc[heredoc_pos++], O_RDONLY);
				if (in_fd == -1)
				{
					perror("minishell: heredoc file open error");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				in_fd = open(in_files[i]->file.value, O_RDONLY);
				if (in_fd == -1)
				{
					perror("minishell: input redirection error");
					exit(EXIT_FAILURE);
				}
			}
		}
		dup_2(in_fd, STDIN_FILENO);
	}
}

static void	open_out_files(t_redirect **out_files)
{
	int	out_fd;
	int	i;
	int	flags;

	out_fd = -1;
	i = 0;
	if (out_files && *out_files)
	{
		while (out_files[i])
		{
			if (out_fd != -1)
				close(out_fd);
			flags = O_WRONLY | O_CREAT | (out_files[i]->type == t_double_greater ? O_APPEND : O_TRUNC);
			out_fd = open(out_files[i]->file.value, flags, 0644);
			if (out_fd == -1)
			{
				perror("minishell: output redirection error");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		dup_2(out_fd, STDOUT_FILENO);
	}
}

void	redirect_io(t_command cmd, char **heredoc, int heredoc_pos)
{
	open_in_files(cmd.in_files, heredoc, heredoc_pos);
	open_out_files(cmd.out_files);
}
