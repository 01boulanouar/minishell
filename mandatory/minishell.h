/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:00:56 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/02 17:19:58 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

# define DELIM " 	"

size_t					ft_strlen(const char *s);
int						ft_isin(const char c, const char *charset);
size_t					ft_strspn(const char *s, const char *accept);
size_t					ft_strcspn(const char *s, const char *reject);
char					*ft_copy(const char *start, const char *end);
#endif
