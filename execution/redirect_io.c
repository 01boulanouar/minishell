/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:24:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 02:46:46 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_in_files(t_redirect **in_files, char **heredoc, int heredoc_pos)
{
	int	i;
	int	in_fd;

	in_fd = -1;
	if (in_files && *in_files)
	{
		i = 0;
		while (in_files[i])
		{
			if (in_fd != -1)
				close(in_fd);
			if (in_files[i]->type == t_double_less)
				in_fd = ft_open(heredoc[heredoc_pos++], O_RDONLY);
			else
				in_fd = ft_open(in_files[i]->file.value, O_RDONLY);
			i++;
		}
		ft_dup2(in_fd, STDIN_FILENO);
	}
}

void	open_out_files(t_redirect **out_files)
{
	int	i;
	int	out_fd;
	int	flags;

	out_fd = -1;
	if (out_files && *out_files)
	{
		i = 0;
		while (out_files[i])
		{
			if (out_fd != -1)
				close(out_fd);
			flags = O_WRONLY | O_CREAT;
			if (out_files[i]->type == t_double_greater)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
			out_fd = ft_open_create(out_files[i]->file.value, flags, 0644);
			i++;
		}
		ft_dup2(out_fd, STDOUT_FILENO);
	}
}

void	redirect_io(t_command cmd, char **heredoc, int heredoc_pos)
{
	open_in_files(cmd.in_files, heredoc, heredoc_pos);
	open_out_files(cmd.out_files);
}
