/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:36 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 22:33:18 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(int oldfd)
{
	int	result;

	result = dup(oldfd);
	ft_error(result);
	ft_close(oldfd);
	register_fd(result);
}
