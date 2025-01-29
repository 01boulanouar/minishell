/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:00:56 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/29 15:07:34 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_word_desc
{
	char				*word;
	int					flags;
}						t_word_desc;

typedef struct s_word_list
{
	t_word_desc			*word;
	struct word_list	*next;
}						t_word_list;

char					**ft_split(char const *s, const char *charset);
char					**ft_free(char **arr, int i);

#endif
