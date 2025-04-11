/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:29:36 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/06 16:06:45 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_command command)
{
	char	**arr;
	char	*path;

	arr = get_command_str(command);
	path = get_command_path(arr[0]);
	if (!arr || !arr[0] || !path)
		ft_exit(*ft_get_exit_status());
	if (execve(path, arr, get_env_str()) == -1)
	{
		print_error(1, arr[0], NULL, "command not found");
		ft_exit(COMMAND_NOT_FOUND);
	}
}
