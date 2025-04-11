/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:59:49 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/02 15:55:29 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_command(char *executable)
{
	struct stat	cmd_stat;

	if (executable && (!ft_strcmp(executable, ".") || !ft_strcmp(executable,
				"..")))
	{
		print_error(1, executable, NULL, "command not found");
		return (ft_set_exit_status(COMMAND_NOT_FOUND), 0);
	}
	if (stat(executable, &cmd_stat) != 0)
	{
		print_error(1, executable, NULL, strerror(errno));
		return (ft_set_exit_status(COMMAND_NOT_FOUND), 0);
	}
	if (S_ISDIR(cmd_stat.st_mode) || executable[ft_strlen(executable)
		- 1] == '/')
	{
		print_error(1, executable, NULL, "Is a directory");
		return (ft_set_exit_status(COMMAND_NOT_EXECUTABLE), 0);
	}
	if (access(executable, X_OK) != 0)
	{
		print_error(1, executable, NULL, "Permission denied");
		return (ft_set_exit_status(COMMAND_NOT_EXECUTABLE), 0);
	}
	return (1);
}

static int	is_local(char *executable)
{
	return (executable[0] == '/' || !ft_strncmp(executable, "./", 2));
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
