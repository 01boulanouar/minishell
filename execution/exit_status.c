/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:51:22 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 01:08:54 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		*ft_get_exit_status()
{
	static int status;
	return (&status);
}

void ft_set_exit_status(int new_status)
{
	int *status;
	status = ft_get_exit_status();
	*status = new_status;
}

