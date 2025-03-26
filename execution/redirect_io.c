/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:24:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/26 01:36:20 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_redirection(t_redirect *file, int *out_fd)
{
	int	flags;

	if (*out_fd != -1)
		close(*out_fd);
	flags = O_WRONLY | O_CREAT;
	if (file->type == t_double_greater)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	*out_fd = ft_open_create(file->file.value, flags, 0644);
}

static void	handle_input_redirection(t_redirect *file, char **heredoc,
		int *heredoc_pos, int *in_fd)
{
	if (*in_fd != -1)
		close(*in_fd);
	if (file->type == t_double_less)
		*in_fd = ft_open(heredoc[(*heredoc_pos)++], O_RDONLY);
	else
		*in_fd = ft_open(file->file.value, O_RDONLY);
}

void	redirect_io(t_command *cmd, char **heredoc, int heredoc_pos)
{
	int			i;
	int			in_fd;
	int			out_fd;
	t_redirect	**files;

	files = cmd->files;
	if (!files || !*files)
		return ;
	in_fd = -2;
	out_fd = -2;
	i = 0;
	while (files[i] && in_fd != -1 && out_fd != -1)
	{
		if (files[i]->type == t_double_greater || files[i]->type == t_greater)
			handle_output_redirection(files[i], &out_fd);
		else
			handle_input_redirection(files[i], heredoc, &heredoc_pos, &in_fd);
		i++;
	}
	if (in_fd == -1 || out_fd == -1)
		cmd->not_to_be_executed = 1;
	if (in_fd != -1)
		ft_dup2(in_fd, STDIN_FILENO);
	if (out_fd != -1)
		ft_dup2(out_fd, STDOUT_FILENO);
}
