/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:41:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/26 21:08:53 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(pid_t *last_pid)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == *last_pid)
		{
			if (WIFEXITED(status))
				ft_set_exit_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				ft_set_exit_status(128 + WTERMSIG(status));
		}
		pid = waitpid(-1, &status, 0);
	}
}
