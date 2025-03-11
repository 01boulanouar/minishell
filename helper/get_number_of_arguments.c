/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_of_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:25:06 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/11 22:25:59 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_number_of_arguments(t_command command)
{
	int	i;

	if (!command.tokens || !command.tokens[0])
		return (0);
	i = 1;
	while (command.tokens[i])
		i++;
	return (i - 1);
}
