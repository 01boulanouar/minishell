/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:41 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/27 04:48:54 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	ft_atol(const char *str)
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

static int	exit_is_valid_status(char *str)
{
	size_t	i;

	if (!str || ft_isallspace(str) || !ft_strcmp(str, "-") || !ft_strcmp(str,
			"+"))
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (i < ft_strlen(str) || ft_atol(str) == LONG_MAX + 1ul)
		return (0);
	return (1);
}

int	exit_builtin(t_command command, int should_exit)
{
	int		ret;
	char	*arg;

	if (should_exit)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (get_number_of_arguments(command) == 0)
		ret = *ft_get_exit_status();
	if (get_number_of_arguments(command) >= 1)
	{
		if (command.tokens[1] && command.tokens[1]->value)
		{
			arg = command.tokens[1]->value;
			if (!exit_is_valid_status(arg))
				(1) && (ret = 255, print_error(1, "exit", arg,
					"numeric argument required"));
			else if (get_number_of_arguments(command) > 1)
				return (print_error(1, "exit", NULL, "too may arguments"), 1);
			else if (get_number_of_arguments(command) == 1)
				ret = ft_atoi(arg);
		}
	}
	if (should_exit)
		ft_exit(ret);
	return (ret);
}
