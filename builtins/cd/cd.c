/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:02 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 02:39:16 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_command command)
{
	int	ret;

	ret = EXIT_FAILURE;
	if (get_number_of_arguments(command) > 1)
	{
		print_error(1, "cd", NULL, "too many arguments");
		return (ret);
	}
	if (!get_number_of_arguments(command) || cd_is_home(command))
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
