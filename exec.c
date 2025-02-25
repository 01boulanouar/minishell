/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/25 17:10:50 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_command *commands, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < get_number_of_commands(tokens))
	{
		if (is_builtin(commands[i]))
			exec_builtin(commands[i]);
		i++;
	}
}
