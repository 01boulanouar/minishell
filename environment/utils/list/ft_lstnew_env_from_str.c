/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env_from_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:14:43 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 18:04:41 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env_from_str(char *str)
{
	char	*start;
	char	*key;
	char	*operator;
	char	*value;

	start = str;
	while (*str)
	{
		if (*str == EQUAL || !ft_strncmp(str, "+=", 2))
			break ;
		str++;
	}
	key = ft_copy_env(start, str);
	start = str;
	if (!ft_strncmp(str, "+=", 2))
		str++;
	if (*str == EQUAL)
		str++;
	operator = ft_copy_env(start, str);
	start = str;
	while (*str)
		str++;
	value = ft_copy_env(start, str);
	return (ft_lstnew_env(key, operator, value));
}
