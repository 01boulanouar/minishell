/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/22 17:40:00 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				heredoc[heredoc_index] = read_from_heredoc(*in_files, heredoc,
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
	pid = ft_fork();
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
			ft_dup2(input_fd, STDIN_FILENO);
		if (!is_last)
			dup2(fd[1], STDOUT_FILENO);
		if (!is_last)
		{
			ft_close(fd[0]);
			ft_close(fd[1]);
		}
		redirect_io(command, herdoc, command.heredoc_pos);
		if (command.tokens[0] && ft_strcmp("exit", command.tokens[0]->value))
		{
			if (is_builtin(command))
				ft_exit(exec_builtin(command));
			if (!path)
			{
				print_error(1, "command not found", NULL, arr[0]);
				ft_exit(COMMAND_NOT_FOUND);
			}
			if (execve(path, arr, get_env_str()) == -1)
			{
				print_error(1, "command not found", NULL, arr[0]);
				ft_exit(COMMAND_NOT_FOUND);
			}
		}
		else
			ft_exit(EXIT_SUCCESS);
	}
	else
	{
		if (!is_last)
			ft_close(fd[1]);
		if (input_fd != STDIN_FILENO)
			ft_close(input_fd);
	}
	return (!is_last * fd[0] + is_last * STDIN_FILENO);
}

void	exec_builtin_alone(t_command command, char **heredoc)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	register_fd(saved_stdin);
	register_fd(saved_stdout);
	redirect_io(command, heredoc, 0);
	exec_builtin(command);
	ft_dup2(saved_stdin, STDIN_FILENO);
	ft_dup2(saved_stdout, STDOUT_FILENO);
}

void	exec(t_command *commands, int n_commands, char **heredoc, int n_herdocs)
{
	int	i;
	int	status;
	int	input_fd;

	i = 0;
	input_fd = STDIN_FILENO;
	if (!commands)
		return ;
	prepare_heredocs(commands, n_commands, heredoc);
	if (n_commands == 1 && is_builtin(commands[0]))
		exec_builtin_alone(commands[0], heredoc);
	else
	{
		while (i < n_commands && commands[i].tokens)
		{
			input_fd = exec_bin(commands[i], input_fd, (i == n_commands - 1),
					heredoc);
			i++;
		}
		while (wait(&status) > 0)
			;
		if (WIFEXITED(status))
			ft_set_exit_status(WEXITSTATUS(status));
	}
	cleanup_heredocs(heredoc, n_herdocs);
}
