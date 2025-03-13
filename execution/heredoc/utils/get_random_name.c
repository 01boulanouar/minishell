/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random_heredoc_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:41:42 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/13 21:50:01 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_random_name(void)
{
	static int	counter;
	char		*num;
	char		*name;

	num = ft_itoa(counter++);
	name = ft_strjoin("heredoc_", num);
	return (name);
}
