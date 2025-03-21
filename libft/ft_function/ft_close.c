/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:28:58 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 22:31:58 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	int	result;

	result = close(fd);
	ft_error(result);
	unregister_fd(fd);
}
