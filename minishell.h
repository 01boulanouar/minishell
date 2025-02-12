/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:05 by moboulan          #+#    #+#             */
/*   Updated: 2025/02/10 17:54:48 by moboulan         ###   ########.fr       */
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
# define BLANKS_QUOTES " 	\'\""
// Error Codes
# define EXIT_SYNTAX_ERROR 258

// Error String
# define SYNTAX_ERROR_STR "minishell: syntax error near unexpected token\n"

// Token types
typedef enum e_token_type
{
	t_pipe,
	t_less,
	t_greater,
	t_word,
	t_squote,
	t_dquote,
}					t_token_type;

// Token struct
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				token_after_space;
	struct s_token	*next;
}					t_token;

// String Utils
size_t				ft_strlen(const char *s);
void				ft_putstr_fd(const char *s, int fd);
int					ft_isin(const char c, const char *charset);
size_t				ft_strspn(const char *s, const char *accept);
size_t				ft_strcspn(const char *s, const char *reject);
char				*ft_copy(const char *start, const char *end);

// List Utils
t_token				*ft_lstnew(char *value, t_token_type type,
						int token_after_space);
void				ft_lstadd_back(t_token **lst, t_token *new);
void				ft_lstfree(t_token **lst);

// Lexer Functions
char				*lex_print_token_type(t_token_type type);
t_token_type		lex_get_token_type(const char *value);
int					lex_is_valid_syntax(const char *line);
char				*lex_trim(char *line);
void				lexer(char *line);

#endif