/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:02 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 06:22:49 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_is_home(t_command command)
{
	if (!command.tokens[1])
		return (0);
	return (!ft_strcmp(command.tokens[1]->value, "--")
		|| !ft_strcmp(command.tokens[1]->value, "~"));
}

static int	cd_handle_home(char *str, char *dir)
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

int	cd_builtin(t_command command)
{
	int	ret;

	ret = EXIT_FAILURE;
	if (get_number_of_arguments(command) > 1)
	{
		print_error(1, "cd", NULL, "too many arguments");
		return (ret);
	}
	if (!get_number_of_arguments(command) || cd_is_home(command) || !ft_strcmp(command.tokens[1]->value, "HOME"))
		cd_handle_home("HOME", NULL);
	else if (!command.tokens[1])
		return (ret);
	else if (!ft_strncmp(command.tokens[1]->value, "~", 1))
		cd_handle_home("HOME", ++(command.tokens[1]->value));
	else if (!ft_strcmp(command.tokens[1]->value, "-"))
		cd_handle_home("OLDPWD", NULL);
	else if (command.tokens[1] && command.tokens[1]->value)
		ret = ft_chdir(command.tokens[1]->value);
	return (EXIT_SUCCESS);
}
