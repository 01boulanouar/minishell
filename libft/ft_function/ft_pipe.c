/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:36 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 22:33:46 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(int fildes[2])
{
	int	result;

	result = pipe(fildes);
	(ft_error(result));
	register_fd(fildes[0]);
	register_fd(fildes[1]);
}
