/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:02 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/08 00:30:55 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (perror("cd"), EXIT_FAILURE);
	if (getcwd(pwd, PATH_MAX))
	{
		ft_update_env("OLDPWD", ft_getenv("PWD"), 0);
		ft_update_env("PWD", pwd, 0);
	}
	else
		print_error(1, "cd", path, GETCWD_ERROR_STR);
	return (EXIT_SUCCESS);
}

static int	is_home(t_command command)
{
	if (!command.tokens[1])
		return (0);
	return (!ft_strcmp(command.tokens[1]->value, "--") \
			|| !ft_strcmp(command.tokens[1]->value, "~"));
}

int	cd_builtin(t_command command)
{
	char	*home;
	int		ret;

	ret = EXIT_SUCCESS;
	if (!get_number_of_arguments(command) || is_home(command))
	{
		if (!ft_getenv("HOME"))
			return (print_error(1, "cd", NULL, "HOME not set"), EXIT_FAILURE);
		home = ft_getenv("HOME");
		ret = ft_chdir(home);
	}
	else if (command.tokens[1] && command.tokens[1]->value)
		ret = ft_chdir(command.tokens[1]->value);
	return (ret);
}
