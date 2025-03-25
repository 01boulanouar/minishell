/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:24:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 05:15:11 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_io(t_command cmd, char **heredoc, int heredoc_pos)
{
	int			i;
	int			in_fd;
	int			out_fd;
	int			flags;
	t_redirect	**files;

	files = cmd.files;
	in_fd = -1;
	out_fd = -1;
	if (!files && !*files)
		return ;
	i = 0;
	while (files[i])
	{
		if (files[i]->type == t_double_greater || files[i]->type == t_greater)
		{
			if (out_fd != -1)
				close(out_fd);
			flags = O_WRONLY | O_CREAT;
			if (files[i]->type == t_double_greater)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
			out_fd = ft_open_create(files[i]->file.value, flags, 0644);
		}
		else
		{
			if (in_fd != -1)
				close(in_fd);
			if (files[i]->type == t_double_less)
				in_fd = ft_open(heredoc[heredoc_pos++], O_RDONLY);
			else
				in_fd = ft_open(files[i]->file.value, O_RDONLY);
		}
		i++;
	}
	if (in_fd != -1)
		ft_dup2(in_fd, STDIN_FILENO);
	if (out_fd != -1)
		ft_dup2(out_fd, STDOUT_FILENO);
	return ;
}
