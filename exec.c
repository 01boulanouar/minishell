/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/04 17:53:50 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_command_str(t_command command)
{
	int i;
	int size;
	char **arr;

	size = get_number_of_arguments(command) + 1;
	arr = ft_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (command.tokens[i] && command.tokens[i]->value)
	{
		arr[i] = ft_strdup(command.tokens[i]->value);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}



char **get_env_str()
{
	int i;
	int size;
	char **arr;
	t_env	**env;
	t_env	*node;


	env = get_env_head();
	node = *env;
	size = ft_lstsize(node) + 1;
	arr = ft_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (node)
	{
		arr[i] = ft_strjoin(node->key, ft_strjoin("=", node->value, 0), 0);
		i++;
		node = node->next;
	}
	arr[i] = NULL;
	return (arr);
}

char *get_command_path(char *executable)
{
	int	i;
	char *path;
	char **split;
	char *full_path;
	struct stat buffer;
	
	path = ft_getenv("PATH");
	split = ft_split(path, ':');
	
	i = 0;
    while (split[i])
    {
    	full_path = ft_strjoin(ft_strjoin(split[i], "/", 0), executable, 0);
        if (stat(full_path, &buffer) == 0) 
            return full_path;
        i++;
    }
    return (NULL); 
}

int	execute(t_command command)
{
	char **arr;
	char *path;
	int  pid;
	int status;
	
	arr = get_command_str(command);
	path = get_command_path(arr[0]);

	pid = fork();

	if (pid == 0)
	{
		if (execve(path, arr, get_env_str()) == -1)
		printf("errooor\n");

	}
	else 
		waitpid(pid , &status, 0);
	return (EXIT_FAILURE);
}

void	exec(t_command *commands)
{
	int	i;

	i = 0;
	while (commands[i].tokens != NULL)
	{
		if (is_builtin(commands[i]))
			exec_builtin(commands[i]);
		else
			execute(commands[i]);
		i++;
	}
}
