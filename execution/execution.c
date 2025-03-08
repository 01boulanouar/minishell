/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/07 23:55:09 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_command_path(char *executable)
{
	int			i;
	char		*path;
	char		**split;
	char		*full_path;
	struct stat	buffer;

	path = ft_getenv("PATH");
	split = ft_split(path, ':');
	i = 0;
	while (split && split[i])
	{
		full_path = ft_strjoin(ft_strjoin(split[i], "/"), executable);
		if (stat(full_path, &buffer) == 0)
			return (full_path);
		else if (stat(executable, &buffer) == 0 && !ft_strncmp(executable, "./",
				2))
			return (executable);
		i++;
	}
	return (NULL);
}

int	execute(t_command command, int input_fd, int is_last)
{
	char	**arr;
	char	*path;
	int		pid;
	int		status;
	int		fd[2];

	arr = get_command_str(command);
	path = get_command_path(arr[0]);
	if (!is_last && pipe(fd) == -1)
	{
		print_error(1, NULL, "pipe error", arr[0]);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (!is_last)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		// if (command.not_to_be_executed == 1)
		// {
		// 	print_error(0, NULL, arr[1], "ambiguous redirect");
		// 	exit(1);
		// }
		if (execve(path, arr, get_env_str()) == -1)
		{
			print_error(0, NULL, "command not found", arr[0]);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (!is_last)
			close(fd[1]);
	}
	return (is_last ? EXIT_SUCCESS : fd[0]);
}

void	exec(t_command *commands, int n_commands)
{
	int	i;
	int	input_fd;

	input_fd = STDIN_FILENO;
	i = 0;
	if (!commands)
		return ;
	while (i < n_commands)
	{
		if (is_builtin(commands[i]))
			exec_builtin(commands[i]);
		else if (commands[i].tokens)
			input_fd = execute(commands[i], input_fd, (i == n_commands - 1));
		i++;
	}
}
