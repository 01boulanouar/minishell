/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:23:24 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/27 02:45:37 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_in_shell;

void	sigint_handler(int signal)
{
	ft_putendl_fd("", STDOUT_FILENO);
	if (g_in_shell == 0)
		ft_set_exit_status(128 + signal);
	if (g_in_shell == 1)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		ft_set_exit_status(1);
	}
	else if (g_in_shell == 2)
	{
		g_in_shell = 3;
		ft_set_exit_status(1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	return ;
}
