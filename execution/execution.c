
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/08 03:24:17 by aelkadir         ###   ########.fr       */
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
		else if (stat(executable, &buffer) == 0 \
			&& (!ft_strncmp(executable, "./", 2) || !ft_strncmp(executable, "/", 1)))
			return (executable);
		i++;
	}
	return (NULL);
}


void	redirect_io(t_command cmd)
{
	int	in_fd;
	int	out_fd;
	int	i;
	int	flags;

	in_fd = -1;
	out_fd = -1;
	// If input redirection exists, open the file
	if (cmd.in_files)
	{
		for (i = 0; cmd.in_files[i]; i++)
		{
			if (in_fd != -1)
				close(in_fd);
			in_fd = open(cmd.in_files[i]->file, O_RDONLY);
			if (in_fd == -1)
			{
				perror("minishell: input redirection error");
				exit(EXIT_FAILURE);
			}
		}
		dup2(in_fd, STDIN_FILENO); // Redirect stdin to the file
		close(in_fd);
	}
	// If output redirection exists, open the file
	if (cmd.out_files)
	{
		for (i = 0; cmd.out_files[i]; i++)
		{
			if (out_fd != -1)
				close(out_fd);
			flags = O_WRONLY | O_CREAT | (cmd.out_files[i]->type == t_double_greater ? O_APPEND : O_TRUNC);
			out_fd = open(cmd.out_files[i]->file, flags, 0644);
			if (out_fd == -1)
			{
				perror("minishell: output redirection error");
				exit(EXIT_FAILURE);
			}
		}
		dup2(out_fd, STDOUT_FILENO); // Redirect stdout to the file
		close(out_fd);
	}
}


void	dup_2(int old, int new)
{
	dup2(old, new);
	close(old);
}
int	execute(t_command command, int input_fd, int is_last)
{
	char	**arr;
	char	*path;
	int		pid;
	int		fd[2];

	arr = get_command_str(command);
	path = get_command_path(arr[0]);
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
		close(fd[0]);
		close(fd[1]);
		redirect_io(command);
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
			close(fd[1]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
	}
	return (!is_last ? fd[0] : STDIN_FILENO);
}

void	exec(t_command *commands, int n_commands)
{
	int i;
	int input_fd;

	i = 0;
	input_fd = STDIN_FILENO;

	if (!commands)
		return ;

	// if there is just one command and it s a builting , do not fork for it
    
	while (i < n_commands)
	{
		input_fd = execute(commands[i], input_fd, (i == n_commands - 1));
		i++;
	}

	// After all commands are executed, wait for the last command to finish
	int status;
	while (wait(&status) > 0)
		;
}