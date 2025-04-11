/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:18:04 by moboulan          #+#    #+#             */
/*   Updated: 2025/04/02 16:18:21 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_current_path(void)
{
	char	**stored_path;
	char	*current_path;

	stored_path = ft_get_path();
	if (stored_path && *stored_path)
		current_path = ft_strdup_env(*stored_path);
	else
		current_path = ft_getcwd();
	return (current_path);
}

static char	*ft_join_paths(char *current, char *path)
{
	char	*result;
	size_t	len;

	if (path[0] == '/')
		return (ft_strdup_env(path));
	len = ft_strlen(current);
	if (len > 0 && current[len - 1] != '/')
		result = ft_strjoin_env(ft_strjoin_env(current, "/"), path);
	else
		result = ft_strjoin_env(current, path);
	return (result);
}

static void	ft_process_parts(char **parts, int *j)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		if (!ft_strcmp(parts[i], "."))
			parts[i] = NULL;
		else if (!ft_strcmp(parts[i], ".."))
		{
			parts[i] = NULL;
			if (*j > 0)
				(*j)--;
		}
		else if (parts[i][0] != '\0')
		{
			if (*j != i)
				parts[*j] = parts[i];
			(*j)++;
		}
		i++;
	}
	parts[*j] = NULL;
}

static char	*ft_rebuild_path(char **parts, int j)
{
	char	*result;
	int		i;

	result = ft_strdup_env("/");
	i = 0;
	while (i < j)
	{
		if (parts[i])
		{
			result = ft_strjoin_env(result, parts[i]);
			if (i + 1 < j)
				result = ft_strjoin_env(result, "/");
		}
		i++;
	}
	return (result);
}

char	*ft_real_path(char *path)
{
	char	*current_path;
	char	*result;
	char	**parts;
	int		j;

	if (!path)
		return (NULL);
	current_path = ft_get_current_path();
	if (!current_path)
		return (NULL);
	result = ft_join_paths(current_path, path);
	if (!result)
		return (NULL);
	parts = ft_split(result, '/');
	if (!parts)
		return (NULL);
	j = 0;
	ft_process_parts(parts, &j);
	result = ft_rebuild_path(parts, j);
	return (result);
}
