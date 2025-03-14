/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 02:53:14 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_builtin(t_command command)
{
	int		ret;
	char	*arg;

	ret = EXIT_FAILURE;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (get_number_of_arguments(command) == 0)
		ret = EXIT_SUCCESS;
	else if (get_number_of_arguments(command) > 1)
		print_error(1, "exit", NULL, "too may arguments");
	else if (command.tokens[1] && command.tokens[1]->value)
	{
		arg = command.tokens[1]->value;
		if (exit_is_valid_status(arg))
			ret = ft_atoi(arg);
		else
		{
			print_error(1, "exit", arg, "numeric argument required");
			ret = EXIT_BUILTIN_BAD_USAGE;
		}
	}
	exit(ret);
}
