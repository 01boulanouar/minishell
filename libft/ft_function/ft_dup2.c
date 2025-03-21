/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:36 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 22:33:14 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int oldfd, int newfd)
{
	int	result;

	result = dup2(oldfd, newfd);
	(ft_error(result));
	ft_close(oldfd);
	register_fd(result);
}
