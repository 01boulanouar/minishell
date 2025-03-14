/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_handle_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:26:31 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 02:38:38 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_handle_home(char *str, char *dir)
{
	char	*path;

	if (!str || !ft_getenv(str))
	{
		print_error(1, "cd", NULL, ft_strjoin(str, " not set"));
		return (EXIT_FAILURE);
	}
	path = ft_strjoin(ft_getenv(str), dir);
	return (ft_chdir(path));
}
