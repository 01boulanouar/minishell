/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:13 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/07 23:25:30 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(t_command command)
{
	char	cwd[PATH_MAX];

	if (get_number_of_arguments(command))
	{
		print_error(1, "pwd", NULL, "too may arguments");
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else
		print_error(1, "pwd", NULL, GETCWD_ERROR_STR);
	return (EXIT_FAILURE);
}
