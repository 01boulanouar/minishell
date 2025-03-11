// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   redirect_io.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/09 17:45:39 by aelkadir          #+#    #+#             */
// /*   Updated: 2025/03/09 22:04:36 by aelkadir         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"


void cleanup_heredocs(char **heredoc, int num_herdocs)
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


char *heredoc_1(t_redirect *redirect, char **heredoc, int heredoc_index)
{
	char *line;
	int fd;
	char *name = get_random_name();

	// Create the file
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc temporary file creation error");
		exit(EXIT_FAILURE);
	}

	// Read the input for the heredoc
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redirect->file.value) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}

	close(fd);
	// // Store the heredoc file name in the static list
	heredoc[heredoc_index++] = ft_strdup(name);

	return name;
}


static void open_in_files(t_redirect **in_files, char **heredoc)
{
    int in_fd = -1;
    int heredoc_pos = 0;

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
		dup_2(out_fd, STDOUT_FILENO); // Redirect stdout to the file
	}
}

void	redirect_io(t_command cmd, char **heredoc)
{
	open_in_files(cmd.in_files, heredoc);
	open_out_files(cmd.out_files);
}