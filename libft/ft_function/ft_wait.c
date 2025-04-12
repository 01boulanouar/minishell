/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:41:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/04/12 16:02:10 by aelkadir         ###   ########.fr       */
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
	restore_terminal_settings();
	g_in_shell = 1;
}
