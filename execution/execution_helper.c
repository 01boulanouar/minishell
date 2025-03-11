/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:41:42 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/10 23:42:50 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char *get_random_name(void)
{
    static int counter ; 
    char *num = ft_itoa(counter++);
    char *name = ft_strjoin("heredoc_", num);
    return name;
}