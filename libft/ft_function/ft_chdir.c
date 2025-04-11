/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:57:40 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/11 15:22:36 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_path_env(char *pwd)
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
	struct stat	stat_path;
	char		*real_path;

	real_path = ft_real_path(path);
	if (!real_path || stat(real_path, &stat_path) == -1
		|| !S_ISDIR(stat_path.st_mode) || access(real_path, X_OK) == -1
		|| chdir(real_path) == -1)
	{
		if (!real_path)
			print_error(1, "cd", path, "Path resolution failed");
		else if (stat(real_path, &stat_path) == -1)
			print_error(1, "cd", path, "No such file or directory");
		else if (!S_ISDIR(stat_path.st_mode))
			print_error(1, "cd", path, "Not a directory");
		else if (access(real_path, X_OK) == -1)
			print_error(1, "cd", path, "Permission denied");
		else
			;
		return (EXIT_FAILURE);
	}
	ft_set_path(real_path);
	update_path_env(real_path);
	return (EXIT_SUCCESS);
}
