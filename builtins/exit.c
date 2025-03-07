/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:00 by moboulan          #+#    #+#             */
/*   Updated: 2025/03/07 23:25:22 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	get_exit_status(int new_status, int set)
// {
// 	static int status;
// 	if (set)
// 		status = new_status;
// 	return (status);
// }

unsigned long long	ft_atol(const char *str)
{
	long long	num;
	int			signe;

	num = 0;
	signe = 1;
	while (ft_isspace(*str))
		str++;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (1);
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			signe *= -1;
	}
	while (ft_isdigit(*str))
	{
		if (num > num * 10 + (*str - '0'))
			return (LONG_MAX + 1ul);
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((long long)num * signe);
}

int	is_valid_exit_status(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (i < ft_strlen(str) || ft_isallspace(str) || (ft_strlen(str) == 1
			&& (str[0] == '-' || str[0] == '+')) || ft_atol(str) == LONG_MAX
		+ 1ul)
		return (0);
	return (1);
}

int	exit_builtin(t_command command)
{
	char	*arg;
	int		status;

	if (get_number_of_arguments(command) == 0)
		exit(EXIT_SUCCESS);
	else if (get_number_of_arguments(command) > 1)
	{
		print_error(1, "exit", NULL, "too may arguments");
		return (EXIT_FAILURE);
	}
	if (command.tokens[1] && command.tokens[1]->value)
	{
		arg = command.tokens[1]->value;
		if (is_valid_exit_status(arg))
		{
			status = ft_atoi(arg);
			exit(status);
		}
		else
		{
			print_error(1, "exit", arg, "numeric argument required");
			exit(EXIT_FAILURE);
		}
	}
	return (EXIT_FAILURE);
}
