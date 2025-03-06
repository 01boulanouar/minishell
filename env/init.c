/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:04:48 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/06 21:16:19 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_empty_env(void)
{
	char	*path;
	char	cwd[PATH_MAX];
	t_env	*node;

	node = ft_lstnew_env_from_str("OLDPWD");
	ft_lstadd_back_env(node);
	path = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	node = ft_lstnew_env_from_str(path);
	ft_lstadd_back_env(node);
	node = ft_lstnew_env_from_str(ft_strjoin("PWD=", getcwd(cwd, PATH_MAX)));
	ft_lstadd_back_env(node);
	node = ft_lstnew_env_from_str("SHLVL=1");
	ft_lstadd_back_env(node);
	node = ft_lstnew_env_from_str("_=/usr/bin/env");
	ft_lstadd_back_env(node);
}

static void	set_shlvl(t_env *node)
{
	int	old_shlvl;

	old_shlvl = ft_atoi(node->value);
	node->value = ft_itoa(old_shlvl + 1);
}

void	init_env(char **line)
{
	t_env	*node;
	int		i;

	i = 0;
	if (line && !line[0])
		init_empty_env();
	while (line[i])
	{
		node = ft_lstnew_env_from_str(line[i]);
		if (!ft_strcmp(node->key, "SHLVL"))
			set_shlvl(node);
		ft_lstadd_back_env(node);
		i++;
	}
}
