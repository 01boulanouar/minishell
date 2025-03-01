/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/01 22:48:29 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_env_head(void)
{
	static t_env	*env;

	return (&env);
}

int	is_valid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != UNDERSCORE)
		return (0);
	while (ft_isvalid(key[i]))
		i++;
	return (ft_strlen(key) == i);
}

void	init_env(char **line)
{
	char	cwd[PATH_MAX];
	t_env	*node;
	int		i;

	i = -1;
	if (line && !line[0])
	{
		node = ft_lstnew_env_from_str("OLDPWD");
		ft_lstadd_back_env(node);
		node = ft_lstnew_env_from_str("PATH=mnbe3d");
		ft_lstadd_back_env(node);
		node = ft_lstnew_env_from_str(ft_strjoin("PWD=", getcwd(cwd, PATH_MAX), 0));
		ft_lstadd_back_env(node);
		node = ft_lstnew_env_from_str("SHLVL=1");
		ft_lstadd_back_env(node);
		node = ft_lstnew_env_from_str("_=/usr/bin/env");
		ft_lstadd_back_env(node);
	}
	while (line[++i])
	{
		node = ft_lstnew_env_from_str(line[i]);
		if (!ft_strcmp(node->key, "SHLVL"))
			node->value = ft_itoa(ft_atoi(node->value) + 1);
		ft_lstadd_back_env(node);
	}
}

char	*ft_getenv(char *name)
{
	t_env	**env;
	t_env	*tmp;

	env = get_env_head();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
