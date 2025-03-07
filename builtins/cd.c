/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:02 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/06 21:51:48 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chdir(char *path)
{
	char		pwd[OPEN_MAX];
	struct stat	stat_path;

	if (stat(path, &stat_path) == -1)
		return (printf("cd: %s: No such file or directory\n", path), EXIT_FAILURE);
	if (!S_ISDIR(stat_path.st_mode))
		return (printf("cd: %s: Not a directory\n", path), EXIT_FAILURE);
	if (chdir(path) == -1)
		return (perror("cd"), EXIT_FAILURE);
	if (getcwd(pwd, OPEN_MAX))
	{
		ft_update_env("OLDPWD", ft_getenv("PWD"), 0);
		ft_update_env("PWD", pwd, 0);
	}
	else
		ft_putstr_fd("minishell: cd: "
			"error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n", 2);
	return (EXIT_SUCCESS);
}

int	cd_builtin(t_command command)
{
	char	*home;
	int		ret;

	ret = EXIT_SUCCESS;
	if (!get_number_of_arguments(command) || (command.tokens[1]
			&& !ft_strcmp(command.tokens[1]->value, "--")))
	{
		home = ft_getenv("HOME");
		ret = ft_chdir(home);
	}
	else if (command.tokens[1] && command.tokens[1]->value)
		ret = ft_chdir(command.tokens[1]->value);
	return (ret);
}
