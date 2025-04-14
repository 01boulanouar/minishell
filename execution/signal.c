/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:23:24 by aelkadir          #+#    #+#             */
/*   Updated: 2025/04/14 13:58:42 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	ft_putendl_fd("", STDOUT_FILENO);
	if (g_in_shell == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_set_exit_status(1);
	}
	else if (g_in_shell == 2)
	{
		g_in_shell = 3;
		ft_set_exit_status(1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	close_all_fds();
	return ;
}

struct termios	*ft_get_termios(void)
{
	static struct termios	saved_termios;

	return (&saved_termios);
}

void	save_terminal_settings(void)
{
	tcgetattr(STDIN_FILENO, ft_get_termios());
}

void	restore_terminal_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, ft_get_termios());
}
