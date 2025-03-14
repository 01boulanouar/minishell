/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/14 00:01:21 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	prepare_heredocs(t_command *commands, int n_commands, char **heredoc)
// {
// 	int			i;
// 	int			heredoc_index;
// 	t_redirect	**in_files;

// 	heredoc_index = 0;
// 	for (i = 0; i < n_commands; i++)
// 	{
// 		in_files = commands[i].in_files;
// 		while (in_files && *in_files)
// 		{
// 			if ((*in_files)->type == t_double_less)
// 			{
// 				heredoc[heredoc_index] = read_from_heredoc(*in_files, heredoc,
// 						heredoc_index);
// 				heredoc_index++;
// 			}
// 			in_files++;
// 		}
// 	}
// }

static int	exec_bin(t_command command)
{
	int		pid;
	char	**arr;
	char	**env;
	char	*path;

	arr = get_command_str(command);
	if (!arr || !arr[0])
		return (EXIT_FAILURE);
	path = get_command_path(arr[0]);
	env = get_env_str();
	if (!path || !env)
		return (EXIT_FAILURE);
	pid = ft_fork();
	if (pid == 0)
	{
		if (execve(path, arr, env) == -1)
		{
			print_error(1, "command not found", NULL, arr[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	return (EXIT_SUCCESS);
}

void	exec(t_command *commands, int n_commands, char **heredoc, int n_herdocs)
{
	int		i;
	int		fd[2];
	int prev_fd[2] = {-1, -1};

	(void) heredoc;
	(void) n_herdocs;

	i = 0;
	if (!commands)
		return ;
	while (i < n_commands && commands[i].tokens && commands[i].tokens[0])
	{
		if (i < n_commands - 1)
			ft_pipe(fd);
		if (prev_fd[0] != -1)
            ft_dup2(prev_fd[0], STDIN_FILENO);
		if (i < n_commands - 1)
			ft_dup2(fd[1], STDOUT_FILENO);
		exec_bin(commands[i]);
		if (i < n_commands - 1)
			ft_close(fd[0]);
        prev_fd[0] = fd[0];
        prev_fd[1] = fd[1];
		i++;
	}
	if (prev_fd[0] != -1)
        ft_close(prev_fd[0]);
	//cleanup_heredocs(heredoc, n_herdocs);
}
