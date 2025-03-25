/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:28:33 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 05:27:55 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int status)
{
	ft_set_exit_status(status);
	close_all_fds();
	ft_free();
	ft_free_env();
	exit(status);
}

//need to close all open fds
