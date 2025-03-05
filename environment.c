/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/05 22:01:11 by moboulan         ###   ########.fr       */
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
		node = ft_lstnew_env_from_str("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
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
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_copy_env(const char *start, const char *end)
{
	int		i;
	char	*copy;

	i = 0;
	copy = ft_malloc_env(end - start + 1);
	while (i < end - start)
	{
		copy[i] = start[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strdup_env(const char *s1)
{
	char	*s2;
	char	*s2_start;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2 = ft_malloc_env(s1_len + 1);
	s2_start = s2;
	while (*s1)
		*(s2++) = *(s1++);
	*s2 = '\0';
	return (s2_start);
}

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	str = (char *)ft_malloc_env(len + 2);
	while (*s1)
		str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = '\0';
	return (str);
}
