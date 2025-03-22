/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_out_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:43:19 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 22:21:42 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
