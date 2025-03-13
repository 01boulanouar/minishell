/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:57:40 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/13 21:57:10 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chdir(char *path)
{
	char		pwd[PATH_MAX];
	struct stat	stat_path;

	if (stat(path, &stat_path) == -1)
	{
		print_error(1, "cd", path, "No such file or directory");
		return (EXIT_FAILURE);
	}
	if (!S_ISDIR(stat_path.st_mode))
	{
		print_error(1, "cd", path, "Not a directory");
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
		return (strerror(errno), EXIT_FAILURE);
	if (getcwd(pwd, PATH_MAX))
	{
		ft_update_env("OLDPWD", ft_getenv("PWD"));
		ft_update_env("PWD", pwd);
	}
	else
		print_error(1, "cd", path, GETCWD_ERROR_STR);
	return (EXIT_SUCCESS);
}
