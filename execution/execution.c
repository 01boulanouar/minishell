/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/12 15:56:03 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_heredocs(t_command *commands, int n_commands, char **heredoc)
{
	int			i;
	int			heredoc_index;
	t_redirect	**files;

	heredoc_index = 0;
	i = 0;
	while (i < n_commands)
	{
		files = commands[i].files;
		while (files && *files)
		{
			if ((*files)->type == t_double_less)
			{
				heredoc[heredoc_index] = read_from_heredoc(*files, heredoc,
						heredoc_index);
				if(!heredoc[heredoc_index])
					return ; 
				heredoc_index++;
			}
			files++;
		}
		i++;
	}
}

void	exec_child(int input_fd, int fd[2], t_command command, char **heredoc)
{
	if (input_fd != STDIN_FILENO)
		ft_dup2(input_fd, STDIN_FILENO);
	if (!command.is_last)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_exit(EXIT_FAILURE);
	}
	if (!command.is_last)
	{
		ft_close(fd[0]);
		ft_close(fd[1]);
	}
	redirect_io(&command, heredoc, command.heredoc_pos);
	if (command.not_to_be_executed)
		ft_exit(EXIT_FAILURE);
	if (command.tokens[0])
	{
		if (!ft_strcmp("exit", command.tokens[0]->value))
			ft_exit(exit_builtin(command, 0));
		else if (is_builtin(command))
			ft_exit(exec_builtin(command));
		ft_execve(command);
	}
	else
		ft_exit(EXIT_SUCCESS);
}

int	exec_bin(t_command command, int input_fd, char **heredoc, int *last_pid)
{
	int	pid;
	int	fd[2];

	g_in_shell = 0;
	if (!command.is_last && pipe(fd) == -1)
		return (perror("minishell: pipe error"), EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork error"), EXIT_FAILURE);
	if (pid == 0){
		signal(SIGINT, SIG_DFL);
  		signal(SIGQUIT, SIG_DFL);
		exec_child(input_fd, fd, command, heredoc);
	}
	else
	{
		*last_pid = pid;
		if (!command.is_last)
			ft_close(fd[1]);
		if (input_fd != STDIN_FILENO)
			ft_close(input_fd);
	}
	return (!command.is_last * fd[0] + command.is_last * STDIN_FILENO);
}

void	exec_builtin_alone(t_command command, char **heredoc)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redirect_io(&command, heredoc, 0);
	if (command.not_to_be_executed)
	{
		ft_set_exit_status(EXIT_FAILURE);
		ft_dup2(saved_stdin, STDIN_FILENO);
		ft_dup2(saved_stdout, STDOUT_FILENO);
		return ;
	}
	if (!ft_strcmp("exit", command.tokens[0]->value))
		ft_set_exit_status(exit_builtin(command, 1));
	else
		ft_set_exit_status(exec_builtin(command));
	ft_dup2(saved_stdin, STDIN_FILENO);
	ft_dup2(saved_stdout, STDOUT_FILENO);
}

int	exec(t_command *commands, int n_commands, char **heredoc, int n_heredocs)
{
	int		i;
	int		input_fd;
	pid_t	last_pid;

	last_pid = -1;
	i = 0;
	input_fd = STDIN_FILENO;
	if (!commands)
		return (0);
	prepare_heredocs(commands, n_commands, heredoc);
	if (g_in_shell == 3)
		return (g_in_shell = 1, 0);
	if (n_commands == 1 && is_builtin(commands[0]))
		exec_builtin_alone(commands[0], heredoc);
	else
	{
		while (i < n_commands && commands[i].tokens)
		{
			input_fd = exec_bin(commands[i], input_fd, heredoc, &last_pid);
			i++;
		}
		ft_wait(&last_pid);
	}
	cleanup_heredocs(heredoc, n_heredocs);
	return (0);
}
