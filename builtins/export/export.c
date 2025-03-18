/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:38:53 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/18 01:32:21 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:38:53 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/16 21:13:24 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:38:53 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/16 21:13:24 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	join_arg(t_token **tokens)
{
	int	j;
	int	i;

	j = 1;
	i = 0;
	while (tokens[i] && tokens[i]->value && tokens[i + j] && tokens[i
		+ j]->value && !tokens[i]->before_space)
	{
		if (!is_operator(tokens[i]) && !is_operator(tokens[i + j]))
		{
			tokens[i]->value = ft_strjoin(tokens[i]->value, tokens[i
					+ j]->value);
			tokens[i]->before_space = tokens[i + j]->before_space;
		}
		j++;
	}
	return (j);
}

int	export_builtin(t_command command)
{
	t_env	*node;
	char	*arg;
	int		ret;
	int		i;
	int		j;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!get_number_of_arguments(command))
		return (export_print());
	while (command.tokens[i] && command.tokens[i]->value)
	{
		j = join_arg(&command.tokens[i]);
		arg = command.tokens[i]->value;
		node = ft_lstnew_env_from_str(arg);
		if (!ft_isvalid_env_key(node->key))
		{
			print_error(1, "export", arg, "not a valid identifier");
			ret = EXIT_FAILURE;
		}
		else
			export_handle_argument(node);
		i += j;
	}
	return (ret);
}
