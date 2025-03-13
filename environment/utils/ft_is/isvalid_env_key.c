/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isvalid_env_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 19:34:10 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != UNDERSCORE)
		return (0);
	while (ft_isalnum(key[i]) || key[i] == UNDERSCORE)
		i++;
	return (ft_strlen(key) == i);
}
