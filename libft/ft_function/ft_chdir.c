/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:57:40 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/13 15:06:49 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_path(char *pwd)
{
	if (ft_isin_env("OLDPWD"))
		ft_update_env("OLDPWD", ft_getenv("PWD"));
	else
		ft_lstadd_back_env(ft_lstnew_env("OLDPWD", "=", ft_getenv("PWD")));
	if (ft_isin_env("PWD"))
		ft_update_env("PWD", pwd);
	else
		ft_lstadd_back_env(ft_lstnew_env("PWD", "=", ft_strdup_env(pwd)));
}

int	ft_chdir(char *path)
{
	char		pwd[PATH_MAX];
	struct stat	stat_path;

	if (stat(path, &stat_path) == -1)
	{
		print_error(1, "cd", path, "No such file or directory");
		return (EXIT_FAILURE);
	}
	else if (!S_ISDIR(stat_path.st_mode))
	{
		print_error(1, "cd", path, "Not a directory");
		return (EXIT_FAILURE);
	}
	else if (access(path, X_OK) == -1)
			print_error(1, "cd", path, "Permission denied");
	if (chdir(path) == -1)
		return (EXIT_FAILURE);
	if (getcwd(pwd, PATH_MAX))
		update_path(pwd);
	else
		print_error(1, "cd", NULL, GETCWD_ERROR_STR);
	return (EXIT_SUCCESS);
}
