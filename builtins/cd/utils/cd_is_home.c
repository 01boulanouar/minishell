/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:26:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 16:27:32 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_is_home(t_command command)
{
	if (!command.tokens[1])
		return (0);
	return (!ft_strcmp(command.tokens[1]->value, "--")
		|| !ft_strcmp(command.tokens[1]->value, "~"));
}
