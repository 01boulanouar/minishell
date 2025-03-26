/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:36 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/26 02:33:26 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_command command)
{
	char	**arr;
	char	*path;

	arr = get_command_str(command);
	path = get_command_path(arr[0]);
	if (!arr || !path)
		ft_exit(*ft_get_exit_status());
	if (execve(path, arr, get_env_str()) == -1)
	{
		print_error(1, "", NULL, "command not found");
		ft_exit(COMMAND_NOT_FOUND);
	}
}
