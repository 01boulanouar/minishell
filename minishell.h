/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 13:46:20 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Tokens
# define SQUOTE '\''
# define DQUOTE '\"'
# define PIPE '|'
# define LESS '<'
# define GREATER '>'

// Separators
# define BLANKS " 	"

// Error codes
# define EXIT_SYNTAX_ERROR 258

// Token types
typedef enum e_token_type
{
	t_unkown,
	t_squote,
	t_dquote,
	t_pipe,
	t_less,
	t_greater,
}					t_token_type;

// Token struct
typedef struct s_token
{
	char			value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

// String Utils
size_t				ft_strlen(const char *s);
void				ft_putstr_fd(const char *s, int fd);
int					ft_isin(const char c, const char *charset);
char				*ft_copy(const char *start, const char *end);

// List Utils
t_token				*ft_lstnew(char value, int type);
void				ft_lstadd_back(t_token **lst, t_token *new);

// Lexer Functions
int					lex_is_valid_syntax(const char *line);
int					lex_is_token(char c);
t_token_type		lex_get_token_type(char c);
char				*lex_trim(const char *line);
void				lexer(char *line);

#endif