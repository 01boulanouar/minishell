/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/13 14:49:46 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else if (ft_getenv("PWD"))
	{
		ft_putendl_fd(ft_getenv("PWD"), STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else
		print_error(1, "pwd", NULL, GETCWD_ERROR_STR);
	return (EXIT_FAILURE);
}
