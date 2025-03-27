/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:59:49 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/27 05:23:31 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_command(char *executable)
{
	struct stat	cmd_stat;

	if (stat(executable, &cmd_stat) != 0)
	{
		print_error(1, executable, NULL, strerror(errno));
		ft_set_exit_status(COMMAND_NOT_FOUND);
		return (0);
	}
	if (S_ISDIR(cmd_stat.st_mode)
		|| executable[ft_strlen(executable) - 1] == '/')
	{
		print_error(1, executable, NULL, "Is a directory");
		ft_set_exit_status(COMMAND_NOT_EXECUTABLE);
		return (0);
	}
	if (access(executable, X_OK) != 0)
	{
		print_error(1, executable, NULL, "Permission denied");
		ft_set_exit_status(COMMAND_NOT_EXECUTABLE);
		return (0);
	}
	return (1);
}

static int	is_local(char *executable)
{
	return ((executable[0] == '/'
			|| executable[ft_strlen(executable) - 1] == '/'
			|| !ft_strncmp(executable, ".", 1)));
}

char	*get_command_path(char *executable)
{
	char	*path;
	char	**split;
	char	*full_path;
	int		i;

	path = ft_getenv("PATH");
	split = ft_split(path, ':');
	full_path = NULL;
	i = 0;
	if (executable && *executable && is_local(executable))
	{
		if (is_valid_command(executable))
			return (executable);
		return (NULL);
	}
	while (split && split[i])
	{
		full_path = ft_strjoin(ft_strjoin(split[i], "/"), executable);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	print_error(1, executable, NULL, "command not found");
	return (ft_set_exit_status(COMMAND_NOT_FOUND), NULL);
}
