/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:17:15 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/11 20:52:38 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(int status)
{
	ft_free_command();
	ft_free_env();
	exit(status);		
}

int	ft_fork(void)
{
	int pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror(errno);
		ft_exit(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_close(int fd)
{
 	int result;

	result = close(fd);
	if (result == -1)
	{
		perror(errno);
		ft_exit(EXIT_FAILURE);
	}
	return (result);
}


int	ft_dup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
	{
		perror(errno);
		ft_exit(EXIT_FAILURE);
	}
	return (newfd);
}

int	ft_dup2(int oldfd, int newfd)
{
 	int result;

	result = dup2(oldfd, newfd);
	if (result == -1)
	{
		perror(errno);
		ft_exit(EXIT_FAILURE);
	}
	return (result);
}

void 	execute(char *command, char *args, char *env[])
{
	int pid;
	int fd[2];

	pid = fork();
	if (pid == 0)
	{
		ft_close(fd[1]);
		ft_dup2(fd[0], STDIN_FILENO);
		if (execve(command, args, env) == -1)
    	{
			print_error(1, NULL, "command not found", args[0]);
			close(fd[0]);
        	ft_exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_close(fd[0]);
		ft_dup2(fd[1], STDOUT_FILENO);
		wait(NULL);
		ft_exit(EXIT_SUCCESS);
	}
}
