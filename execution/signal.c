/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:23:24 by aelkadir          #+#    #+#             */
/*   Updated: 2025/04/12 16:00:42 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_in_shell;

void	sigint_handler(int signal)
{
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
	return ;
}

#include <termios.h>

struct termios g_saved_termios;

void save_terminal_settings(void) {
    tcgetattr(STDIN_FILENO, &g_saved_termios);
}

void restore_terminal_settings(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_termios);
}
