/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:41:07 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/26 02:41:49 by aelkadir         ###   ########.fr       */
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
		if (pid == *last_pid && WIFEXITED(status))
			ft_set_exit_status(WEXITSTATUS(status));
		pid = waitpid(-1, &status, 0);
	}
}
