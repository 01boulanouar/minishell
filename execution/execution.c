
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


#include <fcntl.h>
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



void redirect_io(t_command cmd)
{
    int in_fd = -1;
    int out_fd = -1;
    int i;

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
            int flags = O_WRONLY | O_CREAT | (cmd.out_files[i]->type == t_double_greater ? O_APPEND : O_TRUNC);
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


int execute(t_command command, int input_fd, int is_last)
{
    char    **arr;
    char    *path;
    int     pid;
    int     fd[2];

    arr = get_command_str(command);
    path = get_command_path(arr[0]);

	if (!command.tokens[0])
		return (input_fd);

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

    if (pid == 0) // Child process
    {
        // If it's NOT the first command, read from the previous pipe
        if (input_fd != STDIN_FILENO)
        {
            dup2(input_fd, STDIN_FILENO); // Redirect stdin to the previous command's stdout
            close(input_fd);
        }

        // If it's NOT the last command, redirect stdout to the pipe
        if (!is_last)
        {
            close(fd[0]);  // Close read end in child
            dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
            close(fd[1]);
        }

        // Redirect input/output if needed (fixing redirection logic)
        redirect_io(command);

        // Execute the command
        if (is_builtin(command))
        {
            exit(exec_builtin(command));
        }
		if (execve(path, arr, get_env_str()) == -1)
		{
			print_error(1, arr[0] ,NULL , "command not found");
			exit(1);
		}
    }
    // In the parent process, just close the pipe after forking the child process
    else // Parent process
    {
        // If it's not the last command, we don't wait immediately, just close the write end of the pipe
        if (!is_last)
        {
            close(fd[1]); // Close the write end of the pipe in the parent process
        }
    }
    return (fd[0]); // Return the read end of the pipe to be used by the next command
}

void	exec(t_command *commands, int n_commands)
{
	int	i;
	int	input_fd;

	input_fd = STDIN_FILENO;  // Start with stdin for the first command
	if (!commands)
		return ;

	// Iterate through all commands
	for (i = 0; i < n_commands; i++)
	{
		// Execute each command with input redirection from the previous pipe (if any)
		input_fd = execute(commands[i], input_fd, (i == n_commands - 1)); // Last command gets a special flag
	}

	// After all commands are executed, wait for the last command to finish
	int status;
    while (wait(&status) > 0);

}
