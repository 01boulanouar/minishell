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

void	ft_close(int fd)
{
	if (fd != -1)
		close(fd);
}


void	dup_2(int old, int new)
{
	dup2(old, new);
	close(old);
}

static void	open_in_files(t_redirect **in_files)
{
	int	in_fd;
	int	i;

	in_fd = -1;
	i = 0;
	if (in_files && *in_files)
	{
		while (in_files[i])
		{
			if (in_fd != -1)
				close(in_fd);
			if (in_files[i]->type == t_double_less)
			{
				heredoc(in_files[i]);
				exit(1);
			}
			else
				in_fd = open(in_files[i]->file.value, O_RDONLY);
			if (in_fd == -1)
			{
				perror("minishell: input redirection error");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		dup_2(in_fd, STDIN_FILENO);// Redirect stdin to the file 
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

void	redirect_io(t_command cmd)
{
	open_in_files(cmd.in_files);
	open_out_files(cmd.out_files);
}