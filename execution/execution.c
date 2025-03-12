/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/12 15:52:37 by moboulan         ###   ########.fr       */
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
		else if (stat(executable, &buffer) == 0 && (!ft_strncmp(executable,
					"./", 2) || !ft_strncmp(executable, "/", 1)))
			return (executable);
		i++;
	}
	return (NULL);
}

void	prepare_heredocs(t_command *commands, int n_commands, char **heredoc)
{
	int			i;
	int			heredoc_index;
	t_redirect	**in_files;

	heredoc_index = 0;
	for (i = 0; i < n_commands; i++)
	{
		in_files = commands[i].in_files;
		while (in_files && *in_files)
		{
			if ((*in_files)->type == t_double_less)
			{
				heredoc[heredoc_index] = heredoc_1(*in_files, heredoc,
						heredoc_index);
				heredoc_index++;
			}
			in_files++;
		}
	}
}

int	exec_bin(t_command command, int input_fd, int is_last, char **herdoc)
{
	char	**arr;
	char	*path;

	arr = get_command_str(command);
	path = get_command_path(arr[0]);
	int pid, fd[2];
	if (!is_last && pipe(fd) == -1)
	{
		perror("minishell: pipe error");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
			dup_2(input_fd, STDIN_FILENO);
		if (!is_last)
			dup2(fd[1], STDOUT_FILENO);
		if (!is_last)
		{
			ft_close(fd[0]);
			ft_close(fd[1]);
		}
		redirect_io(command, herdoc, command.heredoc_pos);
		if (is_builtin(command))
			exit(exec_builtin(command));
		if (execve(path, arr, get_env_str()) == -1)
		{
			printf("minishell: command not found: %s\n", arr[0]);
			exit(1);
		}
	}
	else
	{
		if (!is_last)
			ft_close(fd[1]);
		if (input_fd != STDIN_FILENO)
			ft_close(input_fd);
	}
	return (!is_last ? fd[0] : STDIN_FILENO);
}

void	exec(t_command *commands, int n_commands, char **heredoc, int n_herdocs)
{
	int	i;
	int	status;
	int input_fd;

	i = 0;
	input_fd = STDIN_FILENO;
	if (!commands)
		return ;
	prepare_heredocs(commands, n_commands, heredoc);
	if (n_commands == 1 && is_builtin(commands[0]))
	{
		redirect_io(commands[0], heredoc, commands[0].heredoc_pos);
		exec_builtin(commands[0]);
	}
	else
	{
		while (i < n_commands && commands[i].tokens && commands[i].tokens[0])
		{
			input_fd = exec_bin(commands[i], input_fd, (i == n_commands - 1),
					heredoc);
			i++;
		}
		while (wait(&status) > 0)
			;
	}
	cleanup_heredocs(heredoc, n_herdocs);
}
