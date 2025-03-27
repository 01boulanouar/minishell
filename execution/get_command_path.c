/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:59:49 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/27 05:03:00 by moboulan         ###   ########.fr       */
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
	if (S_ISDIR(cmd_stat.st_mode) || executable[ft_strlen(executable)
			- 1] == '/')
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
	if (executable && (executable[0] == '/' || executable[ft_strlen(executable)
				- 1] == '/' || !ft_strncmp(executable, ".", 1)))
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

static int	get_command_len(t_command command)
{
	int	i;

	if (!command.tokens)
		return (0);
	i = 0;
	while (command.tokens[i] && command.tokens[i]->value)
		i++;
	return (i);
}

char	**get_command_str(t_command command)
{
	int		i;
	char	**arr;

	arr = ft_malloc(sizeof(char *) * (get_command_len(command) + 1));
	i = 0;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arr[i] = ft_strdup(command.tokens[i]->value);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**get_env_str(void)
{
	int		i;
	char	**arr;
	t_env	**env;
	t_env	*node;

	env = get_env_list();
	node = *env;
	arr = ft_malloc(sizeof(char *) * (ft_lstsize_env(node) + 1));
	i = 0;
	while (node)
	{
		arr[i] = ft_strjoin(node->key, ft_strjoin("=", node->value));
		i++;
		node = node->next;
	}
	arr[i] = NULL;
	return (arr);
}
