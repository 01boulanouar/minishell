/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_in_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:43:19 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 22:49:08 by moboulan         ###   ########.fr       */
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
