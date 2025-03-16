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

int	export_builtin(t_command command)
{

	t_env	*node;
	char	*arg;
	int		ret;
	int		i;
	int 	j;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!get_number_of_arguments(command))
		return (export_print());
	while (command.tokens[i] && command.tokens[i]->value)
	{
		j=0;
		while(command.tokens[i] && command.tokens[i]->value && command.tokens[i+j+1] && command.tokens[i+j+1]->value )
		{
			if(command.tokens[i+j+1] && !command.tokens[i]->before_space && !is_operator(command.tokens[i]) && !is_operator(command.tokens[i+j+1])) {
				command.tokens[i]->value=ft_strjoin(command.tokens[i]->value, command.tokens[i+j+1]->value);
				command.tokens[i]->before_space=command.tokens[i+j+1]->before_space;
			}
			j++;
		}
		arg = command.tokens[i]->value;
		printf("[%s]\n",arg);
		node = ft_lstnew_env_from_str(arg);
		if (!ft_isvalid_env_key(node->key))
		{
			print_error(1, "export", arg, "not a valid identifier");
			ret = EXIT_FAILURE;
		}
		else
			export_handle_argument(node);
		i += j +(j==0); 
	}
	return (ret);
}
