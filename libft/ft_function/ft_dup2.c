/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:36 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/26 02:08:56 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup2(int oldfd, int newfd)
{
	int	result;

	result = dup2(oldfd, newfd);
	ft_close(oldfd);
	return (result);
}
