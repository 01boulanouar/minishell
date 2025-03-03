/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/03 17:43:37 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: "
			"error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n", 2);
	}
	return (EXIT_FAILURE);
}
