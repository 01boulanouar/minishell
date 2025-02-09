/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/09 16:49:34 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

// Quotes 
# define SQUOTE '\''
# define DQUOTE '\"'

// Error codes
# define EXIT_SYNTAX_ERROR 258

void	ft_putstr_fd(char *s, int fd);

int		is_valid_syntax(char *line);
void	lexer(char *line);

#endif