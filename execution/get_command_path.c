/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:59:49 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/25 08:24:31 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_command(char *executable)
{
	struct stat	cmd_stat;

	if (stat(executable, &cmd_stat) != 0)
	{
		print_error(1, executable, NULL, strerror(errno));
		ft_set_exit_status(COMMAND_NOT_FOUND);
		return (0);
	}

	if (S_ISDIR(cmd_stat.st_mode))
	{
		print_error(1, executable, NULL, "Is a directory");
		ft_set_exit_status(COMMAND_NOT_EXECUTABLE);
		return (0);
	}
	
	if (access(executable, F_OK | X_OK) != 0)
	{
		print_error(1, executable, NULL, "command not found");
		ft_set_exit_status(COMMAND_NOT_EXECUTABLE);
		return (0);
	}

	return (1);
}


char	*get_command_path(char *executable)
{
	int			i;
	char		*path;
	char		**split;
	char		*full_path;


	path = ft_getenv("PATH");
	split = ft_split(path, ':');
	full_path = NULL;

	i = 0;
	while (split && split[i] && executable && ft_strncmp(executable, "./", 2) && executable[0] != '/')
	{
		full_path = ft_strjoin(ft_strjoin(split[i], "/"), executable);
		if (access((const char *)full_path, X_OK) == 0)
			return (full_path);	
		i++;
	}


	if ((full_path == NULL && executable[0] == '/') || (full_path && ft_strcmp(executable, full_path) && executable[0] == '/')
	|| (full_path && ft_strcmp(executable, full_path) && !ft_strncmp(executable, "./", 2))
	|| (full_path == NULL && !ft_strncmp(executable, "./", 2)))
	{
		print_error(1, executable, NULL, "No such file or directory");
		ft_set_exit_status(COMMAND_NOT_FOUND);
		return (NULL);
	}
	
	if (is_valid_command(executable))
			return (executable);
	return (full_path);
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

